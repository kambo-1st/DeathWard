param([string]$OutputJson,[switch]$ValidateOnly)
$ErrorActionPreference='Stop'
# Read-only companion to read-live-motion.ps1. No injected code or game input.
Add-Type -TypeDefinition @'
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
public static class DeathWardLiveFloor {
 [DllImport("kernel32.dll",SetLastError=true)] static extern IntPtr OpenProcess(uint access,bool inherit,int pid);
 [DllImport("kernel32.dll",SetLastError=true)] static extern bool ReadProcessMemory(IntPtr handle,IntPtr address,byte[] buffer,int size,out IntPtr read);
 [DllImport("kernel32.dll")] static extern bool CloseHandle(IntPtr handle);
 static byte[] Read(IntPtr h,long p,int n) {
  if(p<0x10000||p+n>0x100000000L||n<0||n>1024*1024)throw new Exception("Unexpected address or read size");
  var b=new byte[n];IntPtr got;
  if(!ReadProcessMemory(h,new IntPtr(p),b,n,out got)||got.ToInt64()!=n)throw new Exception("Read failed at "+p.ToString("x"));return b;
 }
 static uint U(byte[] b,int o){return BitConverter.ToUInt32(b,o);}
 static uint U(IntPtr h,long p){return U(Read(h,p,4),0);}
 static bool Equal(byte[] a,byte[] b){if(a.Length!=b.Length)return false;for(int i=0;i<a.Length;i++)if(a[i]!=b[i])return false;return true;}
 static Dictionary<string,object> Row(params object[] pairs){var d=new Dictionary<string,object>();for(int i=0;i<pairs.Length;i+=2)d.Add((string)pairs[i],pairs[i+1]);return d;}
 static object Config(IntPtr h,long address) {
  var b=Read(h,address,0x5c);int count=BitConverter.ToUInt16(b,0x44);
  if(count>1024)throw new Exception("Unexpected room spawn count");
  var slots=new List<object>();long baseAddress=U(b,0x40);
  for(int i=0;i<count;i++) {
   var slot=Read(h,baseAddress+16*i,16);int choices=slot[8];long entries=U(slot,4);var values=new List<object>();
   for(int j=0;j<choices;j++) {
    var e=Read(h,entries+12*j,12);
    values.Add(Row("type",U(e,0),"variant",BitConverter.ToUInt16(e,4),"subtype",BitConverter.ToUInt16(e,6),"weight",BitConverter.ToSingle(e,8)));
   }
   slots.Add(Row("x",BitConverter.ToInt16(slot,0),"y",BitConverter.ToInt16(slot,2),"choices",values));
  }
  return Row("type",U(b,8),"variant",U(b,12),"subtype",U(b,16),"difficulty",U(b,0x2c),"weight_at_capture",BitConverter.ToSingle(b,0x34),"allowed_doors",U(b,0x38),"shape_metadata_only",U(b,0x48),"slots",slots,"raw_base64",Convert.ToBase64String(b));
 }
 public static object Capture(int pid,long moduleBase) {
  var h=OpenProcess(0x410,false,pid);if(h==IntPtr.Zero)throw new Exception("VM_READ|QUERY_INFORMATION access failed");
  try {
   long game=U(h,moduleBase+0x7fd65c),room=U(h,game+0x18190);uint frame=U(h,game+0x1a30dc);
   uint stage=U(h,game),stageType=U(h,game+4),difficulty=U(h,game+0x243624),count=U(h,game+0x1815c);long current=U(h,room+4);
   if(difficulty>3)throw new Exception("Unexpected native difficulty enum");
   if(stage!=1||count==0||count>507)throw new Exception("Expected an active first-floor descriptor table; stop before interpreting data");
   long start=game+0x14,delta=current-start;
   if(delta<0||delta%0xb8!=0||delta/0xb8>=count)throw new Exception("Current room does not belong to the expected descriptor table");
   var table=Read(h,start,(int)count*0xb8);var rooms=new List<object>();
   for(int i=0;i<count;i++) {
    int o=i*0xb8;long config=U(table,o+0x10);
    if(config==0)throw new Exception("Missing config inside used descriptor table");
    var raw=new byte[0xb8];Array.Copy(table,o,raw,0,raw.Length);
    rooms.Add(Row("list_index",i,"grid_index",BitConverter.ToInt32(table,o),"safe_grid_index",BitConverter.ToInt32(table,o+4),"dimension",U(table,o+0xc),"actual_doors",U(table,o+0x18),"decoration_seed",U(table,o+0x58),"spawn_seed",U(table,o+0x5c),"award_seed",U(table,o+0x60),"raw_descriptor_base64",Convert.ToBase64String(raw),"config",Config(h,config)));
   }
   // D14a.13: capture the actual run context. A numeric seed does not prove
   // Seeds::IsCustomRun. Offsets are pinned by coin-machine Init/restriction code.
   long manager=U(h,moduleBase+0x7fd680);
   var customRun=Read(h,game+0x1bb04,1);var runFlags=Read(h,game+0x1c3168,8);
   var runRestriction=Read(h,game+0x1c31a0,1);var profileVector=Read(h,manager+0x20a9ac,8);var bank=Read(h,manager+0x31c,4);
   var donationContext=Row("custom_run",customRun[0]!=0,"run_flag17",(U(runFlags,0)&(1u<<17))!=0,"run_flag18",(U(runFlags,0)&(1u<<18))!=0,
    "run_byte1c31a0",runRestriction[0]!=0,"profile_vector_nonempty",U(profileVector,0)!=U(profileVector,4),"bank",BitConverter.ToInt32(bank,0),
    "seed_effect_and_mod_policy_queries_captured",false,"scope","Raw pinned current-run fields; historical shop context and full query results are not inferred.");
   var actors=new List<object>();long actorList=U(h,room+0x125c);uint actorCount=U(h,room+0x1264);
   if(actorCount>4096)throw new Exception("Unexpected active actor count");
   for(uint i=0;i<actorCount;i++) {
    long actor=U(h,actorList+4*i);var identity=Read(h,actor+0x28,12);var position=Read(h,actor+0x294,8);
    var row=Row("type",U(identity,0),"variant",U(identity,4),"subtype",U(identity,8),"x",BitConverter.ToSingle(position,0),"y",BitConverter.ToSingle(position,4));
    // Pinned pickup coin-admission code at0x6be82e reads the signed live price.
    if(U(identity,0)==5)row.Add("price",BitConverter.ToInt32(Read(h,actor+0x480,4),0));
    if(U(identity,0)==1)row.Add("character",U(h,actor+0x130c));actors.Add(row);
   }
   if(U(h,game+0x18190)!=room||U(h,game+0x1a30dc)!=frame||U(h,game+0x1815c)!=count||U(h,game)!=stage||!Equal(table,Read(h,start,table.Length)))throw new Exception("Floor changed during capture; pause and retry with a new output filename");
   if(U(h,moduleBase+0x7fd680)!=manager||!Equal(customRun,Read(h,game+0x1bb04,1))||!Equal(runFlags,Read(h,game+0x1c3168,8))||!Equal(runRestriction,Read(h,game+0x1c31a0,1))||!Equal(profileVector,Read(h,manager+0x20a9ac,8))||!Equal(bank,Read(h,manager+0x31c,4)))throw new Exception("Donation context changed during capture; retry with a new output filename");
   return Row("schema",2,"captured_utc",DateTime.UtcNow.ToString("o"),"pid",pid,"module_base",moduleBase,"stage",stage,"stage_type",stageType,"difficulty",difficulty,"stage_header_raw_base64",Convert.ToBase64String(Read(h,game,0x14)),"descriptor_count",count,"current_list_index",delta/0xb8,"world_frame",frame,"rooms",rooms,"current_room_actors",actors,"donation_context",donationContext,"method","VM_READ only; no writes, injection, suspension, input or game-file edits","limits",new string[]{"Descriptor candidates do not prove resolved pickups, enemies or factory results in unvisited rooms.","Unlocks, seed text and initial inventory need independent confirmation.","Content capture only; source room shapes and connections are excluded from gameplay implementation.","Live field interpretation must be cross-checked against the pinned source configs and log.","Donation context omits the seed-effect/mod-policy query internals; a fresh run cannot establish historical gate inputs."});
  }finally{CloseHandle(h);}
 }
}
'@
if($ValidateOnly){Write-Output 'PASS PowerShell parsing and C# capture compilation; live capture not exercised';return}
if(!$OutputJson){throw 'OutputJson is required'}
if(Test-Path -LiteralPath $OutputJson){throw 'Output must be a new file'}
$processes=@(Get-Process -Name 'isaac-ng' -ErrorAction SilentlyContinue)
if($processes.Count -ne 1){throw 'Exactly one installed Isaac instance must already be running'}
$process=$processes[0]
$expected='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
if((Get-FileHash -LiteralPath $process.Path -Algorithm SHA256).Hash.ToLowerInvariant() -ne $expected){throw 'Executable differs from pinned Repentance1.7.9b'}
$capture=[DeathWardLiveFloor]::Capture($process.Id,$process.MainModule.BaseAddress.ToInt64())
$capture['executable_sha256']=$expected
$json=$capture | ConvertTo-Json -Depth 16
[System.IO.File]::WriteAllText($OutputJson,$json+[Environment]::NewLine,(New-Object System.Text.UTF8Encoding($false)))
Write-Output ('Captured '+$capture['descriptor_count']+' source room descriptors; resolved contents of unvisited rooms remain unverified')
