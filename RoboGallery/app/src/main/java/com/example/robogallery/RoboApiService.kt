package com.example.robogallery

import kotlinx.coroutines.Deferred
import okhttp3.Interceptor
import retrofit2.Retrofit
import retrofit2.http.GET
import retrofit2.http.Query

interface RoboApiService {

    @GET
    fun getRoboImage(
        @Query("search") image: String,
        @Query("set") set: Int = 1
    ) : Deferred<roboImage>

    companion object {

    }

}