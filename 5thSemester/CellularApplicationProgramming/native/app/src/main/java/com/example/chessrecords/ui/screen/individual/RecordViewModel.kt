package com.example.chessrecords.ui.screen.individual

import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.chessrecords.domain.model.Record
import com.example.chessrecords.domain.repo.RecordRepo
import com.example.chessrecords.ui.util.UiEvent
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import javax.inject.Inject
import kotlinx.coroutines.channels.Channel
import kotlinx.coroutines.flow.receiveAsFlow
import kotlinx.coroutines.flow.update

@HiltViewModel
class RecordViewModel @Inject constructor(
    private val repo: RecordRepo,
    private val savedStateHandle: SavedStateHandle
) : ViewModel() {

    private val _state = MutableStateFlow(RecordState())
    val state = _state.asStateFlow()

    private val _event = Channel<UiEvent>()
    val event = _event.receiveAsFlow()

    private fun sendEvent(event: UiEvent) {
        viewModelScope.launch {
            _event.send(event)
        }
    }

    init {
        savedStateHandle.get<String>("id")?.let {
            val id = it.toInt()
            viewModelScope.launch {
                repo.getRecord(id)?.let { record ->
                    _state.update { screenState ->
                        screenState.copy(
                            id = record.id,
                            rating = record.rating,
                            opponentName = record.opponentName,
                            opponentRating = record.opponentRating,
                            opponentProfile = record.opponentProfile,
                            gameOutcome = record.gameOutcome,
                            //gameDateTime = record.gameDateTime,
                            gameOpening = record.gameOpening,
                            gameTag = record.gameTag,
                            /*gameMoves = record.gameMoves,
                            gameImage = record.gameImage,*/
                            notes = record.notes,
                        )
                    }
                }
            }
        }
    }

    fun onEvent(event: RecordEvent) {
        when (event) {
            is RecordEvent.RatingChange -> {
                _state.update {
                    it.copy(
                        rating = event.value
                    )
                }
            }

            is RecordEvent.OpponentNameChange -> {
                _state.update {
                    it.copy(
                        opponentName = event.value
                    )
                }
            }

            is RecordEvent.OpponentRatingChange -> {
                _state.update {
                    it.copy(
                        opponentRating = event.value
                    )
                }
            }

            is RecordEvent.OpponentProfileChange -> {
                _state.update {
                    it.copy(
                        opponentProfile = event.value
                    )
                }
            }

            is RecordEvent.GameOutcomeChange -> {
                _state.update {
                    it.copy(
                        gameOutcome = event.value
                    )
                }
            }

            is RecordEvent.GameOpeningChange -> {
                _state.update {
                    it.copy(
                        gameOpening = event.value
                    )
                }
            }

            is RecordEvent.GameTagChange -> {
                _state.update {
                    it.copy(
                        gameTag = event.value
                    )
                }
            }

            is RecordEvent.NotesChange -> {
                _state.update {
                    it.copy(
                        notes = event.value
                    )
                }
            }

            RecordEvent.NavigateBack -> sendEvent(UiEvent.NavigateBack)
            RecordEvent.Save -> {
                viewModelScope.launch {
                    val state = state.value
                    val record = Record(
                        id = state.id,
                        rating = state.rating,
                        opponentName = state.opponentName,
                        opponentRating = state.opponentRating,
                        opponentProfile = state.opponentProfile,
                        gameOutcome = state.gameOutcome,
                        //gameDateTime = state.gameDateTime,
                        gameOpening = state.gameOpening,
                        gameTag = state.gameTag,
                        /*gameMoves = state.gameMoves,
                        gameImage = state.gameImage,*/
                        notes = state.notes,
                    )
                    if (state.id == null) {
                        repo.addRecord(record)
                    } else {
                        repo.updateRecord(record)
                        sendEvent(UiEvent.NavigateBack)
                    }
                    sendEvent(UiEvent.NavigateBack)
                }
            }

            RecordEvent.DeleteRecord -> {
                viewModelScope.launch {
                    val state = state.value
                    val record = Record(
                        id = state.id,
                        rating = state.rating,
                        opponentName = state.opponentName,
                        opponentRating = state.opponentRating,
                        opponentProfile = state.opponentProfile,
                        gameOutcome = state.gameOutcome,
                        //gameDateTime = state.gameDateTime,
                        gameOpening = state.gameOpening,
                        gameTag = state.gameTag,
                        /*gameMoves = state.gameMoves,
                        gameImage = state.gameImage,*/
                        notes = state.notes,
                    )
                    repo.deleteRecord(record)
                }
                sendEvent(UiEvent.NavigateBack)
            }

            else -> {}
        }
    }
}