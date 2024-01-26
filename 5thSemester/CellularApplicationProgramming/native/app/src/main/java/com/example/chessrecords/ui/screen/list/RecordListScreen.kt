package com.example.chessrecords.ui.screen.list

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.rounded.Add
import androidx.compose.material3.Divider
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.FloatingActionButton
import androidx.compose.material3.Icon
import androidx.compose.material3.ListItem
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import com.example.chessrecords.domain.model.Record

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun RecordListScreen(
    recordList: List<Record>,
    onRecordClick: (Record) -> Unit,
    onAddRecordClick: () -> Unit
) {
    Scaffold(
        floatingActionButton = {
            FloatingActionButton(
                onClick = onAddRecordClick
            ) {
                Icon(
                    imageVector = Icons.Rounded.Add,
                    contentDescription = "add record"
                )
            }
        }
    ) { padding ->
        LazyColumn(
            contentPadding = PaddingValues(
                start = 20.dp,
                end = 20.dp,
                top = 15.dp + padding.calculateTopPadding(),
                bottom = 15.dp + padding.calculateBottomPadding()
            )
        ) {
            item {
                Column {
                    Text(
                        text = "Chess Games Records",
                        style = MaterialTheme.typography.headlineLarge.copy(textAlign = TextAlign.Center),
                        modifier = Modifier.fillMaxWidth()
                    )
                    Spacer(modifier = Modifier.height(20.dp))
                    Divider(color = Color.White, thickness = 1.dp, modifier = Modifier.fillMaxWidth())
                }
                Spacer(modifier = Modifier.height(10.dp))
            }

            items(recordList) { record ->
                Spacer(modifier = Modifier.height(5.dp))
                Surface(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(4.dp),
                    color = Color.Gray,
                    shape = MaterialTheme.shapes.medium
                ) {
                    ListItem(
                        modifier = Modifier.clickable(
                            onClick = {
                                onRecordClick(record)
                            }
                        ),
                        headlineText = {
                            Text(
                                text = record.gameOpening + " V " + record.opponentName,
                                style = MaterialTheme.typography.titleLarge,
                                color = Color.White
                            )
                        },
                        supportingText = {
                            Column {
                                Text(
                                    text = record.rating.toString(),
                                    style = MaterialTheme.typography.titleMedium,
                                    color = Color.White
                                )
                                Text(
                                    text = record.gameOutcome,
                                    style = MaterialTheme.typography.titleMedium,
                                    color = Color.White
                                )
                            }
                        }
                    )
                }
            }
        }
    }
}