package com.example.chessrecords.data.di

import android.content.Context
import androidx.room.Room
import com.example.chessrecords.data.local.RecordDatabase
import com.example.chessrecords.data.repo.RecordRepoImplementation
import com.example.chessrecords.domain.repo.RecordRepo
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object AppModule{

    @Provides
    @Singleton
    fun provideRecordDatabase(@ApplicationContext context: Context): RecordDatabase =
        Room.databaseBuilder(
            context,
            RecordDatabase::class.java,
            RecordDatabase.name
        ).build()

    @Provides
    @Singleton
    fun provideRecordRepository(@ApplicationContext context: Context, database: RecordDatabase): RecordRepo =
        RecordRepoImplementation(context = context, dao = database.dao)
}