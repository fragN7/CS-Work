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
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.unit.dp

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun RecordAddScreen(
    state: RecordState,
    onEvent: (RecordEvent) -> Unit
) {

    var showDialog by remember { mutableStateOf(false) }

    if (showDialog) {
        AlertDialog(
            onDismissRequest = { showDialog = false },
            title = { Text("Error") },
            text = { Text("Please fill the required fields.") },
            confirmButton = {
                Button(
                    onClick = { showDialog = false }
                ) {
                    Text("OK")
                }
            }
        )
    }

    Scaffold(
        topBar = {
            CenterAlignedTopAppBar(
                title = { "New Game" },
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
                value = state.rating?.takeIf { it != 0 }?.toString() ?: "",
                onValueChange = {
                    val newRating = it.toIntOrNull()
                    newRating?.let { validRating ->
                        onEvent(RecordEvent.RatingChange(validRating))
                    }
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = "Your rating *")
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
                    Text(text = "Opponent's Name *")
                }
            )
            OutlinedTextField(
                value = state.opponentRating?.takeIf { it != 0 }?.toString() ?: "",
                onValueChange = {
                    val newRating = it.toIntOrNull()
                    newRating?.let { validRating ->
                        onEvent(RecordEvent.OpponentRatingChange(validRating))
                    }
                },
                modifier = Modifier.fillMaxWidth(),

                placeholder = {
                    Text(text = "Opponent's Rating *")
                },
                keyboardOptions = KeyboardOptions.Default.copy(keyboardType = KeyboardType.Number)
            )

            OutlinedTextField(
                value = state.opponentProfile?.toString() ?: "",
                onValueChange = {
                    onEvent(RecordEvent.OpponentProfileChange(it))
                },
                modifier = Modifier.fillMaxWidth(),

                placeholder = {
                    Text(text = "Opponent's Profile Link")
                }
            )
            OutlinedTextField(
                value = state.gameOutcome,
                onValueChange = {
                    onEvent(RecordEvent.GameOutcomeChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = "Game Outcome *")
                }
            )
            /*OutlinedTextField(
                value = state.gameDateTime.toString(),
                onValueChange = {
                    onEvent(RecordEvent.GameDateTimeChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
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
                    Text(text = "Game Opening *")
                }
            )
            OutlinedTextField(
                value = state.gameTag?.toString() ?: "",
                onValueChange = {
                    onEvent(RecordEvent.GameTagChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = "Game Tag")
                }
            )

            OutlinedTextField(
                value = state.notes?.toString() ?: "",
                onValueChange = {
                    onEvent(RecordEvent.NotesChange(it))
                },
                modifier = Modifier.fillMaxWidth(),
                placeholder = {
                    Text(text = "Notes")
                }
            )

            Box(
                modifier = Modifier.fillMaxWidth(),
                contentAlignment = Alignment.Center
            ) {
                Button(
                    onClick = {
                        if (validateFields(state)) {
                            onEvent(RecordEvent.Save)
                        } else {
                            showDialog = true                        }
                    },
                    modifier = Modifier.fillMaxWidth(0.5f)
                ) {
                    Text(text = "Add Game")
                }
            }
        }
    }
}

fun validateFields(state: RecordState): Boolean {
    return state.rating != null &&
            !state.opponentName.isNullOrEmpty() &&
            state.opponentRating != null &&
            !state.gameOutcome.isNullOrEmpty() &&
            !state.gameOpening.isNullOrEmpty()
}
