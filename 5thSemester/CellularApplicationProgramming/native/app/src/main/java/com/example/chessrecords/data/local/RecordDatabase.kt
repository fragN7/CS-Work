package com.example.chessrecords.data.local

import androidx.room.Database
import androidx.room.RoomDatabase
import com.example.chessrecords.data.local.dao.RecordDao
import com.example.chessrecords.data.local.entity.RecordEntity

@Database(
    version = 1,
    entities = [RecordEntity::class]
)
abstract class RecordDatabase : RoomDatabase() {

    abstract val dao: RecordDao

    companion object {
        const val name = "recordDB"
    }
}