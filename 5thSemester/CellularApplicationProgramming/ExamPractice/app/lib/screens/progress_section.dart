import 'package:connectivity_plus/connectivity_plus.dart';
import 'package:fitness_tracker/screens/project_data_page.dart';
import 'package:flutter/material.dart';
import 'package:logger/logger.dart';

import '../api/api.dart';
import '../api/network.dart';
import '../widgets/message.dart';

class ProgressSection extends StatefulWidget {
  const ProgressSection({super.key});

  @override
  _ProgressSectionState createState() => _ProgressSectionState();
}

class _ProgressSectionState extends State<ProgressSection> {
  var logger = Logger();
  bool online = true;
  late List<String> projects = [];
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
      getInProgressProjects();
    });
  }

  getInProgressProjects() async {
    if (!mounted) return;
    setState(() {
      isLoading = true;
    });
    logger.log(Level.info, 'getInProgressProjects');
    try {
      projects = await ApiService.instance.getInProgressProjects();
    } catch (e) {
      logger.log(Level.error, e.toString());
      message(context, "Error loading items from server", "Error");
    }
    setState(() {
      isLoading = false;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('In progress'),
      ),
      body: isLoading
          ? const Center(child: CircularProgressIndicator())
          : SizedBox(
          height: MediaQuery.of(context).size.height,
          child: ListView(
            children: [
              ListView.builder(
                itemBuilder: ((context, index) {
                  return Card(
                      color: Colors.white,
                      shadowColor: const Color.fromRGBO(0, 0, 0, 1),
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(18.0),
                      ),
                      child: ListTile(
                        title: Text(projects[index]),
                        onTap: () {
                          Navigator.push(
                              context,
                              MaterialPageRoute(
                                  builder: (context) =>
                                      ProjectDataPage(extractId(projects[index]))));
                        },
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(18.0),
                          side: const BorderSide(
                            color: Colors.grey,
                            width: 1.0,
                          ),
                        ),
                      ));
                }),
                itemCount: projects.length,
                padding: const EdgeInsets.all(10),
                physics: const ScrollPhysics(),
                shrinkWrap: true,
                scrollDirection: Axis.vertical,
              ),
            ],
          )),
    );
  }

  @override
  void dispose() {
    super.dispose();
  }
}

int extractId(String projectString) {
  // Find the index of the first space
  int spaceIndex = projectString.indexOf(' ');

  // Extract the substring from the start to the first space
  String idSubstring = projectString.substring(0, spaceIndex);

  // Convert the substring to an integer
  int? id = int.tryParse(idSubstring);

  // Check if conversion was successful
  return id!;
}
