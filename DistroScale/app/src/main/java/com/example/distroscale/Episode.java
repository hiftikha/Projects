package com.example.distroscale;

public class Episode {

    private String title;
    private String imgUrl;
    private String videoUrl;

    public Episode(String t, String img, String url){
        title = t;
        imgUrl = img;
        videoUrl = url;
    }

    public String getTitle() {
        return title;
    }

    public String getImgUrl() {
        return imgUrl;
    }

    public String getVideoUrl() {
        return videoUrl;
    }
}
