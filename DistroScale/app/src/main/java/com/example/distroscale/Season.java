package com.example.distroscale;

public class Season {
    private String name;
    private Episode[] episodes;

    public Season(String n, Episode[] e){
        name = n;
        episodes = e;
    }

    public Episode getEpisode(int i){
        return episodes[i];
    }
}
