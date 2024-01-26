package com.example.chessrecords

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.example.chessrecords.data.server.ApiInterface
import com.example.chessrecords.domain.model.Record
import com.example.chessrecords.ui.screen.individual.RecordAddScreen
import com.example.chessrecords.ui.screen.individual.RecordScreen
import com.example.chessrecords.ui.screen.individual.RecordUpdateScreen
import com.example.chessrecords.ui.screen.individual.RecordViewModel
import com.example.chessrecords.ui.screen.list.RecordListScreen
import com.example.chessrecords.ui.screen.list.RecordListViewModel
import com.example.chessrecords.ui.theme.ChessRecordsTheme
import com.example.chessrecords.ui.util.Route
import com.example.chessrecords.ui.util.UiEvent
import dagger.hilt.android.AndroidEntryPoint
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

@AndroidEntryPoint
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContent {
            ChessRecordsTheme {
                val navController = rememberNavController()

                NavHost(
                    navController = navController,
                    startDestination = Route.recordList
                ) {
                    composable(route = Route.recordList) {
                        val viewModel = hiltViewModel<RecordListViewModel>()
                        val recordList by viewModel.recordList.collectAsStateWithLifecycle()

                        RecordListScreen(
                            recordList = recordList,
                            onRecordClick = {
                                navController.navigate(
                                    Route.record.replace(
                                        "{id}",
                                        it.id.toString()
                                    )
                                )
                            },
                            onAddRecordClick = {
                                navController.navigate(Route.recordAdd)
                            }
                        )
                    }

                    composable(route = Route.record){
                        val viewModel = hiltViewModel<RecordViewModel>()
                        val state by viewModel.state.collectAsStateWithLifecycle()

                        LaunchedEffect(key1 = true) {
                            viewModel.event.collect { event ->
                                when (event) {
                                    is UiEvent.NavigateBack -> {
                                        navController.popBackStack()
                                    }

                                    else -> Unit
                                }
                            }
                        }

                        RecordScreen(
                            state = state,
                            onEvent = viewModel::onEvent,
                            onUpdateRecord = {
                                navController.navigate(
                                    Route.recordUpdate.replace(
                                        "{id}",
                                        it.id.toString()
                                    )
                                )
                            }
                        )
                    }

                    composable(route = Route.recordAdd) {
                        val viewModel = hiltViewModel<RecordViewModel>()
                        val state by viewModel.state.collectAsStateWithLifecycle()

                        LaunchedEffect(key1 = true) {
                            viewModel.event.collect { event ->
                                when (event) {
                                    is UiEvent.NavigateBack -> {
                                        navController.popBackStack()
                                    }

                                    else -> Unit
                                }
                            }
                        }

                        RecordAddScreen(
                            state = state,
                            onEvent = viewModel::onEvent
                        )
                    }

                    composable(route = Route.recordUpdate) {
                        val viewModel = hiltViewModel<RecordViewModel>()
                        val state by viewModel.state.collectAsStateWithLifecycle()

                        LaunchedEffect(key1 = true) {
                            viewModel.event.collect { event ->
                                when (event) {
                                    is UiEvent.NavigateBack -> {
                                        navController.popBackStack()
                                    }

                                    else -> Unit
                                }
                            }
                        }

                        RecordUpdateScreen(
                            state = state,
                            onEvent = viewModel::onEvent
                        )
                    }
                }
            }
        }
    }
}