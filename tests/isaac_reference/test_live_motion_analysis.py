"""Negative controls for observational timing: an outer loop is not locomotion."""
import csv,importlib.util,tempfile,unittest
from pathlib import Path
root=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('analysis',root/'scripts/isaac-reference/analyze-live-motion.py');A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
class LiveMotionAnalysis(unittest.TestCase):
 def capture(self,motion_hz=None,paused=False,at_wall=False,torn=False):
  temporary=tempfile.TemporaryDirectory();self.addCleanup(temporary.cleanup);p=Path(temporary.name)/'samples.csv';rows=[]
  for n in range(301):
   t=n/200;phase=int(t*60);frame=0 if paused else int(t*30);velocity=4.41423845 if motion_hz else 0
   x=569.5522 if at_wall else 100+(velocity*motion_hz*t if motion_hz else 0)
   rows.append(dict(seconds=t,read_end_seconds=t+.0001,phase_before=phase,phase_after=phase+int(torn),world_before=frame,world_after=frame,manager_state=2,x=x,y=280,vx=velocity,vy=0,friction=1,base_friction=1,time_scale=1,speed=1,previous_vx=velocity,previous_vy=0,flags=0,restore_position=0))
  with p.open('w',newline='') as f:w=csv.DictWriter(f,fieldnames=list(rows[0]));w.writeheader();w.writerows(rows)
  return A.analyze(p)
 def test_paused_loop_does_not_verify_walking(self):
  result=self.capture(paused=True);self.assertEqual(result['outer_phase_hz_over_whole_capture'],60);self.assertFalse(result['live_steady_motion_measured']);self.assertEqual(result['active_gameplay_windows'],0)
 def test_idle_gameplay_does_not_verify_walking(self):
  result=self.capture();self.assertGreater(result['active_gameplay_windows'],0);self.assertFalse(result['live_steady_motion_measured'])
 def test_30_motion_is_not_doubled_by_60_outer_loop(self):
  result=self.capture(motion_hz=30);self.assertTrue(result['live_steady_motion_measured']);self.assertAlmostEqual(result['steady_walking_segments'][0]['effective_motion_invocations_per_second'],30,places=5)
 def test_60_motion_is_measured_from_positions(self):
  result=self.capture(motion_hz=60);self.assertAlmostEqual(result['steady_walking_segments'][0]['effective_motion_invocations_per_second'],60,places=5)
 def test_wall_velocity_is_not_unimpeded_motion(self):self.assertFalse(self.capture(motion_hz=60,at_wall=True)['live_steady_motion_measured'])
 def test_position_changes_without_gameplay_frames_are_not_accepted(self):self.assertFalse(self.capture(motion_hz=60,paused=True)['live_steady_motion_measured'])
 def test_phase_crossing_reads_are_excluded(self):self.assertFalse(self.capture(motion_hz=60,torn=True)['live_steady_motion_measured'])
if __name__=='__main__':unittest.main()
