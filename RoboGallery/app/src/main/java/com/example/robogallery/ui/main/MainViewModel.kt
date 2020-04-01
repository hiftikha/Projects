package com.example.robogallery.ui.main

import android.util.Log
import androidx.lifecycle.ViewModel
import com.example.robogallery.RoboGallery
import com.example.robogallery.RoboItem
import com.example.robogallery.RoboRepository

class MainViewModel(private var roboRepository: RoboRepository) : ViewModel() {

    private var selectedRobot : Int = 0
    private var set : Int = 0

    fun addPhoto(searchTerm: String, set: Int = 0) {
        roboRepository.addRobot(RoboItem(searchTerm, set))
    }

    fun getPhoto(index: Int) : RoboItem {
        return roboRepository.getRobot(index)
    }

    fun getPhotos() = roboRepository.getRobots()

    fun removePhoto(index: Int) {
        roboRepository.removeRobot(index)
    }

    fun getSize() : Int {
        return roboRepository.getSize()
    }

    fun setSelectedRobot(index: Int) {
        selectedRobot = index
    }

    fun getSelectedRobot() : Int {
        return selectedRobot
    }

    fun setSet(set : Int) {
        this.set = set
    }

    fun getSet() : Int {
        return set
    }

    fun resetSet() {
        set = 0
    }
}
