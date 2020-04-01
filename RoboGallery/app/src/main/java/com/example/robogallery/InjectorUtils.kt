package com.example.robogallery

object InjectorUtils {

    fun provideQuotesViewModelFactory() : MainViewModelFactory {
        val repository = RoboRepository.getInstance(Database.getInstance().roboGallery)
        return MainViewModelFactory(repository)
    }
}