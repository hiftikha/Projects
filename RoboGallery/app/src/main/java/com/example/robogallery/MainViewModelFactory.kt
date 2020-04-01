package com.example.robogallery

import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import com.example.robogallery.ui.main.MainViewModel

class MainViewModelFactory(private val roboRepository: RoboRepository) :
    ViewModelProvider.NewInstanceFactory() {

    @Suppress("UNCHECKED_CAST")
    override fun <T : ViewModel?> create(modelClass: Class<T>): T {
        return MainViewModel(roboRepository) as T
    }
}