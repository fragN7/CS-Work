package com.example.chessrecords.data.local.entity

import android.media.Image
import androidx.room.Entity
import androidx.room.PrimaryKey
import java.util.Date

@Entity
data class RecordEntity(
    @PrimaryKey val id: Int?,
    val rating: Int,

    val opponentName: String,
    val opponentRating: Int,
    val opponentProfile: String?,

    val gameOutcome: String,
    //val gameDateTime: Date?,
    val gameOpening: String,
    val gameTag: String?,
    /*val gameMoves: List<String>?,
    val gameImage: Image?,*/

    val notes: String?
)