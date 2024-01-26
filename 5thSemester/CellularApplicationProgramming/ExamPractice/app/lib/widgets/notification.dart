import 'dart:convert';

import 'package:fitness_tracker/models/fitness_data.dart';
import 'package:flutter/material.dart';
import 'package:flutter/scheduler.dart';
import 'package:web_socket_channel/web_socket_channel.dart';

import 'message.dart';

class DataNotification extends StatelessWidget {
  final channel = WebSocketChannel.connect(Uri.parse('ws://localhost:2426'));

  DataNotification({super.key});

  @override
  Widget build(BuildContext context) {
    return StreamBuilder(
        builder: (context, snapshot) {
          SchedulerBinding.instance.addPostFrameCallback((_) {
            if (snapshot.hasData) {
              var data =
                  FintessData.fromJson(jsonDecode(snapshot.data.toString()));
              message(context, data.toString(), "Data added");
            }
          });
          return const Text('');
        },
        stream: channel.stream.asBroadcastStream());
  }
}
