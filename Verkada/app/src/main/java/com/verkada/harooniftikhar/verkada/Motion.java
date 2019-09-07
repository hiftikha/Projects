package com.verkada.harooniftikhar.verkada;

public class Motion {

    private int[][] motionZones;
    private long startTime;
    private long endTime;

    public Motion(int[][] zones, long start, long end){
        motionZones = zones;
        startTime = start;
        endTime = end;
    }

    public int[][] getZones(){
        return motionZones;
    }

    public long getStartTime(){
        return startTime;
    }

    public long getEndTime(){
        return endTime;
    }
}
