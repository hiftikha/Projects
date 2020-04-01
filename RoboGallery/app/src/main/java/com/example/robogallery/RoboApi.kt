package com.example.robogallery

object RoboApi {
    val url = "https://robohash.org/"
    val set = "?set=set"
    val format = ".png"

    fun getPhoto(roboItem: RoboItem) : String {
        return url + roboItem.searchTerm + format + set + roboItem.set
    }
}