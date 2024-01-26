package com.example.chessrecords.data.local.dao

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import com.example.chessrecords.data.local.entity.RecordEntity
import kotlinx.coroutines.flow.Flow

@Dao
interface RecordDao {

    @Query("SELECT * FROM RecordEntity")
    fun getAllRecords(): Flow<List<RecordEntity>>
    @Query("""
        SELECT * FROM RecordEntity
        WHERE id =:id
    """)
    suspend fun getRecord(id: Int): RecordEntity
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun addRecord(recordEntity: RecordEntity)
    @Delete
    suspend fun deleteRecord(recordEntity: RecordEntity)
    @Update
    suspend fun updateRecord(recordEntity: RecordEntity)
}