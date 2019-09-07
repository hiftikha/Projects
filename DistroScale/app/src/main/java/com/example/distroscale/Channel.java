package com.example.distroscale;

public class Channel {
    private String name;
    private Integer id;

    public Channel(Integer i, String n){
        name = n;
        id = i;
    }

    public String getTitle(){
        return name;
    }

    public Integer getID(){
        return id;
    }
}
