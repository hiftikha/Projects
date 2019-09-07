package com.example.distroscale;

public class MovieItem {
    private int channel;
    private String name;
    private String imageUrl;
    private String movieUrl;
    private Season season = null;

    public MovieItem(int c, String n, String img, String url){
        channel = c;
        name = n;
        imageUrl = img;
        movieUrl = url;
    }

    public String getTitle(){
        return name;
    }

    public String getImg(){
        return imageUrl;
    }

    public String getVid(){
        return movieUrl;
    }

    public Season getSeason() {
        return season;
    }
}
