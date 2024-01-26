package com.example.chessrecords.data.mapper

import com.example.chessrecords.data.local.entity.RecordEntity
import com.example.chessrecords.domain.model.Record
fun RecordEntity.asExternalModel(): Record = Record(
    id, rating, opponentName, opponentRating, opponentProfile, gameOutcome, gameOpening, gameTag, notes
)

fun Record.toEntity(): RecordEntity = RecordEntity(
    id, rating, opponentName, opponentRating, opponentProfile, gameOutcome, gameOpening, gameTag, notes
)