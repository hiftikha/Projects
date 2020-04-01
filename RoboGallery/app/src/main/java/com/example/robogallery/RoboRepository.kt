package com.example.robogallery

class RoboRepository private constructor(private val roboGallery: RoboGallery) {

    fun addRobot(robot: RoboItem) {
        roboGallery.addPhoto(robot)
    }

    fun getRobots() = roboGallery.getPhotos()

    fun getSize() = roboGallery.photoList.size

    fun getRobot(index: Int) = roboGallery.getPhoto(index)

    fun removeRobot(index: Int) {
        roboGallery.removePhoto(index)
    }

    companion object {
        @Volatile private var instance: RoboRepository? = null
        fun getInstance(roboGallery: RoboGallery) = instance ?: synchronized(this) {
            instance ?: RoboRepository(roboGallery).also { instance = it}
        }
    }
}