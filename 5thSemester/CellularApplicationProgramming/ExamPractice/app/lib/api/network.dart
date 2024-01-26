import 'dart:async';

import 'package:connectivity_plus/connectivity_plus.dart';

class NetworkConnectivity {
  NetworkConnectivity._();

  static final _instance = NetworkConnectivity._();
  static NetworkConnectivity get instance => _instance;
  final _networkConnectivity = Connectivity();
  final _controller = StreamController.broadcast();
  Stream get myStream => _controller.stream.asBroadcastStream();

  // 1.
  void initialize() async {
    ConnectivityResult result = await _networkConnectivity.checkConnectivity();
    _checkStatus(result);
    _networkConnectivity.onConnectivityChanged.listen((result) {
      print(result);
      _checkStatus(result);
    });
  }

  // 2.
  void _checkStatus(ConnectivityResult result) async {
      var connectivityResult = await Connectivity().checkConnectivity();
      bool isOnline = (connectivityResult == ConnectivityResult.mobile || connectivityResult == ConnectivityResult.wifi);

      _controller.sink.add({connectivityResult: isOnline});
  }

  void disposeStream() => _controller.close();
}
