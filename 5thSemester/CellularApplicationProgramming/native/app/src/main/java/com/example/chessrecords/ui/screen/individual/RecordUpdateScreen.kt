package com.example.chessrecords.ui.screen.individual

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.rounded.ArrowBack
import androidx.compose.material3.Button
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.unit.dp

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun RecordUpdateScreen(
    state: RecordState,
    onEvent: (RecordEvent) -> Unit
) {

    Scaffold(
        topBar = {
            CenterAlignedTopAppBar(
                title = {
                    Text("Update ${state.gameOpening} v ${state.opponentName}")
                },
                navigationIcon = {
                    IconButton(
                        onClick = {
                            onEvent(RecordEvent.NavigateBack)
                        }
                    ) {
                        Icon(
                            imageVector = Icons.Rounded.ArrowBack,
                            contentDescription = "Go Back"
                        )
                    }
                }
            )
        }
    ) { padding ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(padding)
                .padding(
                    horizontal = 20.dp,
                    vertical = 15.dp
                ),
            verticalArrangement = Arrangement.spacedBy(10.dp)
        ) {
            OutlinedTextField(
                value = state.rating.toString(),
                onValueChange = {
                    val newRating = it.toIntOrNull()
                    newRating?.let { validRating ->
                        onEvent(RecordEvent.RatingChange(validRating))
                    }
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = state.rating.toString())
                },
                keyboardOptions = KeyboardOptions.Default.copy(keyboardType = KeyboardType.Number)
            )
            OutlinedTextField(
                value = state.opponentName,
                onValueChange = {
                    onEvent(RecordEvent.OpponentNameChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = state.opponentName.toString())
                }
            )
            OutlinedTextField(
                value = state.opponentRating.toString(),
                onValueChange = {
                    val newRating = it.toIntOrNull()
                    newRating?.let { validRating ->
                        onEvent(RecordEvent.OpponentRatingChange(validRating))
                    }
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = state.opponentRating.toString())
                },
                keyboardOptions = KeyboardOptions.Default.copy(keyboardType = KeyboardType.Number)
            )
            OutlinedTextField(
                value = state.opponentProfile.toString(),
                onValueChange = {
                    onEvent(RecordEvent.OpponentProfileChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = state.opponentProfile.toString())
                }
            )
            OutlinedTextField(
                value = state.gameOutcome,
                onValueChange = {
                    onEvent(RecordEvent.GameOutcomeChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = state.gameOutcome)
                }
            )
            /*OutlinedTextField(
                value = state.gameDateTime.toString(),
                onValueChange = {
                    onEvent(RecordEvent.GameDateTimeChange(it))
                },
                placeholder = {
                    Text(text = "Game's Date")
                }
            )*/
            OutlinedTextField(
                value = state.gameOpening,
                onValueChange = {
                    onEvent(RecordEvent.GameOpeningChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = state.gameOpening)
                }
            )
            OutlinedTextField(
                value = state.gameTag.toString(),
                onValueChange = {
                    onEvent(RecordEvent.GameTagChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = state.gameTag.toString())
                }
            )

            OutlinedTextField(
                value = state.notes.toString(),
                onValueChange = {
                    onEvent(RecordEvent.NotesChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = state.notes.toString())
                }
            )

            Box(
                modifier = Modifier.fillMaxWidth(),
                contentAlignment = Alignment.Center
            ) {
                Button(
                    onClick = {
                        onEvent(RecordEvent.Save)
                    },
                    modifier = Modifier.fillMaxWidth(0.5f)
                ) {
                    Text(text = "Save Game")
                }
            }
        }
    }
}