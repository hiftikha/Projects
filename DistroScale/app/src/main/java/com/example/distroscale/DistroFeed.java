package com.example.distroscale;

public class DistroFeed {
    private static DistroFeed instance = null;

    private Channel[] channels;
    private MovieItem[] movies;

    private DistroFeed(){

    }

    public static DistroFeed getInstance(){
        if (instance == null){
            instance = new DistroFeed();
        }
        return instance;
    }

    public void setMovies(MovieItem[] m){
        movies = m;
    }

    public void setChannels(Channel[] c) {
        channels = c;
    }

    public MovieItem[] getMovies() {
        return movies;
    }

    public Channel[] getChannels() {
        return channels;
    }
}
