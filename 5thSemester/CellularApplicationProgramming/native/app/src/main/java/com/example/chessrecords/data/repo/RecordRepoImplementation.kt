package com.example.chessrecords.data.repo

import android.content.Context
import android.net.ConnectivityManager
import android.net.NetworkCapabilities
import com.example.chessrecords.data.local.dao.RecordDao
import com.example.chessrecords.data.mapper.asExternalModel
import com.example.chessrecords.data.mapper.toEntity
import com.example.chessrecords.data.server.ApiInterface
import com.example.chessrecords.domain.model.Record
import com.example.chessrecords.domain.repo.RecordRepo
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.flow
import kotlinx.coroutines.flow.map
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

class RecordRepoImplementation(private val context: Context, private val dao: RecordDao) : RecordRepo{

    private val api: ApiInterface by lazy {
        createApi()
    }

    private fun createApi(): ApiInterface {
        val retrofit = Retrofit.Builder()
            .addConverterFactory(GsonConverterFactory.create())
            .baseUrl("https://localhost:7186/")
            .build()

        return retrofit.create(ApiInterface::class.java)
    }
    override fun getAllRecords(): Flow<List<Record>> {
        val localRecords = dao.getAllRecords().map { records ->
            records.map {
                it.asExternalModel()
            }
        }

        if (isOnline(context)) {
            return flow { api.getRecords() }
            //TODO: sync local db with server
        }

        return localRecords
    }

    override suspend fun getRecord(id: Int): Record? {

        val localRecord = dao.getRecord(id)?.asExternalModel()

        if (isOnline(context)) {
            return api.getRecord(id)
            //TODO: sync local db with server
        }

        return localRecord
    }

    override suspend fun addRecord(record: Record) {
        dao.addRecord(record.toEntity())

        if (isOnline(context)) {
            api.createRecord(record)
            //TODO: sync local db with server
        }
    }

    override suspend fun deleteRecord(record: Record) {
        dao.deleteRecord(record.toEntity())

        if(isOnline(context)){
            record.id?.let { api.deleteRecord(it) }
            //TODO: sync local db with server
        }
    }

    override suspend fun updateRecord(record: Record) {
        dao.updateRecord(record.toEntity())

        if(isOnline(context)){
            record.id?.let { api.updateRecord(it, record) }
            //TODO: sync local db with server
        }
    }

    private fun isOnline(context: Context): Boolean {
        val connectivityManager =
            context.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager

        return if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) {
            val network = connectivityManager.activeNetwork
            val capabilities = connectivityManager.getNetworkCapabilities(network)
            capabilities?.hasCapability(NetworkCapabilities.NET_CAPABILITY_INTERNET) == true
        } else {
            @Suppress("DEPRECATION")
            val activeNetworkInfo = connectivityManager.activeNetworkInfo
            activeNetworkInfo?.isConnected == true
        }
    }
}
