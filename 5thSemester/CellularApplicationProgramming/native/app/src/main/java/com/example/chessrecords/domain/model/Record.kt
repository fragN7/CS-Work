package com.example.chessrecords.domain.model

import android.icu.text.SimpleDateFormat
import android.media.Image
import java.util.Date

data class Record(
    val id: Int? = null,
    val rating: Int = 0,

    val opponentName: String = "",
    val opponentRating: Int = 0,
    val opponentProfile: String? = null,

    val gameOutcome: String = "",
    //val gameDateTime: Date = SimpleDateFormat("dd/MM/yyyy").parse("01/01/1900"),
    val gameOpening: String = "",
    val gameTag: String? = null,
    /*val gameMoves: List<String>? = null,
    val gameImage: Image? = null,*/

    val notes: String? = null
)