package com.example.chessrecords.domain.repo

import com.example.chessrecords.domain.model.Record
import kotlinx.coroutines.flow.Flow

interface RecordRepo {

    fun getAllRecords(): Flow<List<Record>>
    suspend fun getRecord(id: Int) : Record?
    suspend fun addRecord(record: Record)
    suspend fun deleteRecord(record: Record)
    suspend fun updateRecord(record: Record)
}