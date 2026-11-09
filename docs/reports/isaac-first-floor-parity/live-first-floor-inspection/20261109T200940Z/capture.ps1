param([double]$DurationSeconds=90,[Parameter(Mandatory=$true)][string]$OutputCsv)
$ErrorActionPreference='Stop'
if(Test-Path -LiteralPath $OutputCsv){throw 'Output must be a new file'}
if($DurationSeconds -le 0 -or $DurationSeconds -gt 600){throw 'Duration must be within (0,600] seconds'}
Add-Type -TypeDefinition @'
using System;
using System.IO;
using System.Globalization;
using System.Diagnostics;
using System.Threading;
using System.Runtime.InteropServices;
public static class DeathWardLiveMotion {
 [DllImport("kernel32.dll",SetLastError=true)] static extern IntPtr OpenProcess(uint access,bool inherit,int pid);
 [DllImport("kernel32.dll",SetLastError=true)] static extern bool ReadProcessMemory(IntPtr handle,IntPtr address,byte[] buffer,int size,out IntPtr read);
 [DllImport("kernel32.dll")] static extern bool CloseHandle(IntPtr handle);
 static byte[] Read(IntPtr h,long p,int n){var b=new byte[n];IntPtr got;if(!ReadProcessMemory(h,new IntPtr(p),b,n,out got)||got.ToInt64()!=n)throw new Exception("Read failed at "+p.ToString("x"));return b;}
 static uint U(IntPtr h,long p){return BitConverter.ToUInt32(Read(h,p,4),0);}
 static float F(IntPtr h,long p){return BitConverter.ToSingle(Read(h,p,4),0);}
 public static string Capture(int pid,long moduleBase,double seconds,string output){
  var h=OpenProcess(0x410,false,pid);if(h==IntPtr.Zero)throw new Exception("VM_READ|QUERY_INFORMATION access failed");
  try{
   long game=U(h,moduleBase+0x7fd65c),manager=U(h,moduleBase+0x7fd680),room=U(h,game+0x18190);
   long list=U(h,room+0x125c),player=0;uint count=U(h,room+0x1264);if(count>4096)throw new Exception("Unexpected actor count");
   for(uint i=0;i<count;i++){long actor=U(h,list+4*i);if(U(h,actor+0x28)==1){player=actor;break;}}
   if(player==0)throw new Exception("No native player available");
   long descriptor=U(h,room+4),data=descriptor==0?0:U(h,descriptor+0x10);uint shape=data==0?0:U(h,data+0x48);
   string metadata=String.Format(CultureInfo.InvariantCulture,"pid={0},base={1},game={2},manager={3},room={4},player={5},state={6},shape={7},grid_width={8},grid_height={9},left={10:R},top={11:R},right={12:R},bottom={13:R},speed={14:R},character={15},stopwatch_hz={16}",pid,moduleBase,game,manager,room,player,U(h,manager+8),shape,U(h,room+0xc),U(h,room+0x10),F(h,room+0x14),F(h,room+0x18),F(h,room+0x1c),F(h,room+0x20),F(h,player+0x14ac),U(h,player+0x130c),Stopwatch.Frequency);
   File.WriteAllText(output+".metadata.txt",metadata+Environment.NewLine);
   long start=Stopwatch.GetTimestamp();int samples=0;string stop="duration";
   using(var writer=new StreamWriter(output,false)){
    writer.WriteLine("seconds,read_end_seconds,phase_before,phase_after,world_before,world_after,manager_state,x,y,vx,vy,friction,base_friction,time_scale,speed,previous_vx,previous_vy,flags,restore_position");
    while(true){
     long stamp=Stopwatch.GetTimestamp();double elapsed=(stamp-start)/(double)Stopwatch.Frequency;if(elapsed>=seconds)break;
     if(U(h,game+0x18190)!=room){stop="room_changed";break;}
     uint phase=U(h,manager+0x4a264),frame=U(h,game+0x1a30dc),state=U(h,manager+8);
     var b=Read(h,player+0x28c,0x6c);var cached=Read(h,player+0x14ac,0xf4);var flags=Read(h,player+0x160,0xe);
     uint afterFrame=U(h,game+0x1a30dc),afterPhase=U(h,manager+0x4a264);double end=(Stopwatch.GetTimestamp()-start)/(double)Stopwatch.Frequency;
     object[] row={elapsed,end,phase,afterPhase,frame,afterFrame,state,BitConverter.ToSingle(b,8),BitConverter.ToSingle(b,12),BitConverter.ToSingle(b,0x2c),BitConverter.ToSingle(b,0x30),BitConverter.ToSingle(b,0x38),BitConverter.ToSingle(b,0x34),BitConverter.ToSingle(b,0x68),BitConverter.ToSingle(cached,0),BitConverter.ToSingle(cached,0xe8),BitConverter.ToSingle(cached,0xec),BitConverter.ToUInt32(flags,0),flags[0xd]};
     for(int i=0;i<row.Length;i++){if(i>0)writer.Write(',');writer.Write(Convert.ToString(row[i],CultureInfo.InvariantCulture));}writer.WriteLine();samples++;Thread.Sleep(2);
    }
   }
   return metadata+",samples="+samples+",stop="+stop+",method=VM_READ only; no writes, injected code, suspension or game-file edits; normal keyboard input supplied by separate guarded thread";
  }finally{CloseHandle(h);}
 }
}
'@
$process=Get-Process -Name 'isaac-ng' | Select-Object -First 1
if(!$process){throw 'Installed Isaac must already be running'}
$expected='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
if((Get-FileHash -LiteralPath $process.Path -Algorithm SHA256).Hash.ToLowerInvariant() -ne $expected){throw 'Executable differs from pinned 1.7.9b'}
Add-Type -TypeDefinition @'
using System;
using System.Threading;
using System.Runtime.InteropServices;
public static class DeathWardNativeKeys {
 [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
 [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
 [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h,int n);
 [DllImport("user32.dll")] static extern uint MapVirtualKey(uint k,uint m);
 [DllImport("user32.dll")] static extern void keybd_event(byte k,byte s,uint f,UIntPtr e);
 public static string result="not_started";
 public static bool Press(IntPtr h,byte key,int milliseconds) {
  if(GetForegroundWindow()!=h)return false;
  byte scan=(byte)MapVirtualKey(key,0);
  try {keybd_event(key,scan,0,UIntPtr.Zero);Thread.Sleep(milliseconds);}
  finally {keybd_event(key,scan,2,UIntPtr.Zero);}
  return true;
 }
 public static Thread Begin(IntPtr h) {
  var t=new Thread(()=>{Thread.Sleep(500);bool a=Press(h,65,600);Thread.Sleep(300);bool d=Press(h,68,600);result="A="+a+",D="+d;});
  t.IsBackground=true;t.Start();return t;
 }
}
'@
[void][DeathWardNativeKeys]::ShowWindow($process.MainWindowHandle,9)
[void][DeathWardNativeKeys]::SetForegroundWindow($process.MainWindowHandle)
Start-Sleep -Milliseconds 100
if(![DeathWardNativeKeys]::Press($process.MainWindowHandle,13,100)){throw 'Isaac not foreground; no input capture started'}
$inputThread=[DeathWardNativeKeys]::Begin($process.MainWindowHandle)
Write-Output 'Read-only memory capture with ordinary Enter/A/D input; no process writes.'

[DeathWardLiveMotion]::Capture($process.Id,$process.MainModule.BaseAddress.ToInt64(),$DurationSeconds,$OutputCsv)

$inputThread.Join()
Write-Output ([DeathWardNativeKeys]::result)
$rows=Import-Csv -LiteralPath $OutputCsv
if([uint32]$rows[-1].world_after -gt [uint32]$rows[0].world_before){
 $paused=[DeathWardNativeKeys]::Press($process.MainWindowHandle,27,100)
 Write-Output ('pause_key_sent='+$paused)
} else {Write-Output 'world_did_not_advance; no pause toggle sent'}
