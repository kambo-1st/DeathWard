#!/usr/bin/env python3
"""Analyze read-only native motion samples without treating a paused loop as gameplay."""
import argparse,csv,json,math,statistics
from pathlib import Path

def slope(points):
    tx=statistics.mean(x for x,y in points);ty=statistics.mean(y for x,y in points)
    denominator=sum((x-tx)**2 for x,y in points)
    return sum((x-tx)*(y-ty) for x,y in points)/denominator if denominator else 0

def analyze(path):
    rows=[]
    with path.open() as stream:
        for r in csv.DictReader(stream):
            if None in r.values():continue
            try:rows.append({k:float(v) for k,v in r.items()})
            except ValueError:continue
    if len(rows)<2:raise ValueError('Need at least two complete observations')
    stable=[r for r in rows if r['phase_before']==r['phase_after'] and r['world_before']==r['world_after']]
    duration=rows[-1]['seconds']-rows[0]['seconds']
    outer=(rows[-1]['phase_after']-rows[0]['phase_before'])/duration
    active=[];start=0
    for end,r in enumerate(stable):
        while stable[start]['seconds']<r['seconds']-1.05:start+=1
        left=stable[start];dt=r['seconds']-left['seconds'];frames=r['world_before']-left['world_before']
        if dt>=.9 and frames>=20 and r['manager_state']==left['manager_state']==2:
            active.append({'seconds':r['seconds'],'world_hz':frames/dt,'outer_hz':(r['phase_before']-left['phase_before'])/dt})
    segments=[]
    # Do not infer key-release times from velocity. Select only unimpeded,
    # straight steady walking and fit observed positions against real timestamps.
    for axis,other,lo,hi in [('x','y',60,580),('y','x',140,420)]:
        current=[];sign=0
        def flush():
            nonlocal current
            if len(current)>=10 and current[-1]['seconds']-current[0]['seconds']>=.20:
                cached=statistics.mean(r['v'+axis] for r in current)
                measured=slope([(r['seconds'],r[axis]) for r in current])
                displacement=current[-1][axis]-current[0][axis]
                if abs(displacement)>30 and abs(cached)>1 and current[-1]['world_before']-current[0]['world_before']>=5:
                    extra={'native_coordinates_per_outer_phase':slope([(r['phase_before'],r[axis]) for r in current]),'fitted_outer_hz':slope([(r['seconds'],r['phase_before']) for r in current]),'fitted_world_hz':slope([(r['seconds'],r['world_before']) for r in current]),'speed_stat_range':[min(r['speed'] for r in current),max(r['speed'] for r in current)],'native_cached_velocity_range':[min(r['v'+axis] for r in current),max(r['v'+axis] for r in current)],'time_scale_range':[min(r['time_scale'] for r in current),max(r['time_scale'] for r in current)],'friction_range':[min(r['friction'] for r in current),max(r['friction'] for r in current)]}
                    extra['motion_steps_per_outer_phase']=extra['native_coordinates_per_outer_phase']/cached
                    segments.append({**extra,'axis':axis,'start_seconds':current[0]['seconds'],'end_seconds':current[-1]['seconds'],'samples':len(current),'native_cached_velocity':cached,'fitted_native_coordinates_per_second':measured,'effective_motion_invocations_per_second':measured/cached,'world_frames':current[-1]['world_before']-current[0]['world_before'],'displacement':displacement})
            current=[]
        for r in stable:
            v=r['v'+axis];direction=1 if v>0 else -1
            ordinary=(r['manager_state']==2 and abs(r['speed']-1)<1e-5 and 4.40<=abs(v)<=4.43 and abs(r['v'+other])<.02 and lo+20<r[axis]<hi-20)
            contiguous=not current or r['seconds']-current[-1]['seconds']<.05
            if not ordinary or direction!=sign or not contiguous:flush()
            if ordinary:current.append(r);sign=direction
        flush()
    return {'input':str(path),'sample_rows':len(rows),'stable_sample_rows':len(stable),'torn_or_phase_crossing_rows_excluded':len(rows)-len(stable),'elapsed_seconds':duration,'outer_phase_hz_over_whole_capture':outer,'world_frame_advance':rows[-1]['world_after']-rows[0]['world_before'],'active_gameplay_windows':len(active),'active_gameplay_world_hz_median':statistics.median(r['world_hz'] for r in active) if active else None,'active_gameplay_outer_hz_median':statistics.median(r['outer_hz'] for r in active) if active else None,'steady_walking_segments':segments,'live_steady_motion_measured':bool(segments),'status':'steady live motion observed; inspect identity/geometry and segment agreement' if segments else 'live movement not measured; paused/idle samples do not verify player speed','limitations':['ReadProcessMemory is observational and not an atomic whole-game snapshot; phase-crossing rows filtered','Only observed actor/session/room; no claim for all characters/items/statuses','No exact input-release time is recorded; no live stopping acceptance from these rows','Outer phase rate alone is not player movement frequency']}

def main():
    p=argparse.ArgumentParser();p.add_argument('capture',type=Path);p.add_argument('--output',type=Path);a=p.parse_args();result=analyze(a.capture);text=json.dumps(result,indent=2)+'\n'
    if a.output:a.output.write_text(text)
    print(text,end='')
if __name__=='__main__':main()
