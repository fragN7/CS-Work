import 'package:connectivity_plus/connectivity_plus.dart';
import 'package:fitness_tracker/models/fitness_data.dart';
import 'package:fitness_tracker/models/project.dart';
import 'package:flutter/material.dart';
import 'package:logger/logger.dart';

import '../api/api.dart';
import '../api/network.dart';
import '../services/database_helper.dart';
import '../widgets/message.dart';

class ProjectDataPage extends StatefulWidget {
  final int _id;
  const ProjectDataPage(this._id, {super.key});

  @override
  State<StatefulWidget> createState() => _FitnessDataPageState();
}

class _FitnessDataPageState extends State<ProjectDataPage> {
  var logger = Logger();
  bool online = true;
  late ProjectData data = ProjectData(name: '', team: '', details: '', status: '', members: 0, type: '');
  bool isLoading = false;
  Map _source = {ConnectivityResult.none: false};
  final NetworkConnectivity _connectivity = NetworkConnectivity.instance;
  String string = '';

  @override
  void initState() {
    super.initState();
    connection();
  }

  void connection() {
    _connectivity.initialize();
    _connectivity.myStream.listen((source) {
      _source = source;
      var newStatus = true;
      switch (_source.keys.toList()[0]) {
        case ConnectivityResult.mobile:
          string =
              _source.values.toList()[0] ? 'Mobile: online' : 'Mobile: offline';
          break;
        case ConnectivityResult.wifi:
          string =
              _source.values.toList()[0] ? 'Wifi: online' : 'Wifi: offline';
          newStatus = _source.values.toList()[0] ? true : false;
          break;
        case ConnectivityResult.none:
        default:
          string = 'Offline';
          newStatus = false;
      }
      if (online != newStatus) {
        online = newStatus;
      }
      getProject();
    });
  }

  getProject() async {
    if (!mounted) return;
    setState(() {
      isLoading = true;
    });
    logger.log(Level.info, "Online - $online");
    try {
      if (online) {
        data = await ApiService.instance.getProject(widget._id);
      } else {
        data = await DatabaseHelper.getProject(widget._id);
      }
    } catch (e) {
      logger.e(e);
      message(context, "Error when retreiving data from server", "Error");
    }
    setState(() {
      isLoading = false;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget._id.toString()),
      ),
      body: isLoading
          ? const Center(child: CircularProgressIndicator())
          : Center(
        child: Card(
          shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(18.0),
            side: const BorderSide(
              color: Colors.grey,
              width: 1.0,
            ),
          ),
          child: ListTile(
            title: Text(data.name),
            subtitle: Text(
              'Team: ${data.team}, Details: ${data.details}, Status: ${data.status}, Members: ${data.members}, Type: ${data.type}',
            ),
          ),
        ),
      ),
    );
  }

}
