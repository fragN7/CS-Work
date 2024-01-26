package com.example.chessrecords.data.server

import com.example.chessrecords.domain.model.Record
import retrofit2.Call
import retrofit2.http.Body
import retrofit2.http.DELETE
import retrofit2.http.GET
import retrofit2.http.Headers
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path

interface ApiInterface {

    @Headers("Host: <calculated when request is sent>")
    @GET(value = "records/all")
    fun getRecords(): List<Record>
    @GET(value = "records/{id}")
    fun getRecord(@Path("id") recordId: Int): Record
    @POST("records")
    fun createRecord(@Body record: Record): Record
    @PUT("records/{id}")
    fun updateRecord(@Path("id") recordId: Int, @Body updatedRecord: Record): Record
    @DELETE("records/{id}")
    fun deleteRecord(@Path("id") recordId: Int): Record
}