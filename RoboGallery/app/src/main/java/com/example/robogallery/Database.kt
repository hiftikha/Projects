package com.example.robogallery

class Database private constructor(){

    var roboGallery = RoboGallery()
        private set

    companion object {
        @Volatile private var instance: Database? = null
        fun getInstance() = instance ?: synchronized(this) {
            instance ?: Database().also { instance = it}
        }
    }
}