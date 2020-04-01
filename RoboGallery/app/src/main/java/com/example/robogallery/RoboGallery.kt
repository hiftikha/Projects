package com.example.robogallery

import androidx.databinding.ObservableInt
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData

class RoboGallery(val photoList: MutableList<RoboItem> = mutableListOf(), val photos: MutableLiveData<List<RoboItem>> = MutableLiveData()) {

    init {
        photos.value = photoList
    }

    fun addPhoto(photo: RoboItem) {
        photoList.add(photo)
        photos.value = photoList
    }

    fun getPhoto(index: Int) : RoboItem{
        return photoList[index]
    }

    fun getPhotos() = photos as LiveData<List<RoboItem>>

    fun removePhoto(index: Int) {
        photoList.removeAt(index)
        photos.value = photoList
    }
}