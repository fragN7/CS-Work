package com.example.chessrecords.ui.screen.individual

import android.media.Image

sealed interface RecordEvent {
    data class RatingChange(val value: Int): RecordEvent
    data class OpponentNameChange(val value: String): RecordEvent
    data class OpponentRatingChange(val value: Int): RecordEvent
    data class OpponentProfileChange(val value: String?): RecordEvent
    data class GameOpeningChange(val value: String): RecordEvent
    data class GameDateTimeChange(val value: String): RecordEvent
    data class GameOutcomeChange(val value: String): RecordEvent
    data class GameTagChange(val value: String?): RecordEvent
    data class GameMovesChange(val value: List<String>?): RecordEvent
    data class GameImageChange(val value: Image?): RecordEvent
    data class NotesChange(val value: String?): RecordEvent
    object Save : RecordEvent
    object NavigateBack : RecordEvent
    object DeleteRecord : RecordEvent
}