import 'package:connectivity_plus/connectivity_plus.dart';
import 'package:fitness_tracker/models/fitness_data.dart';
import 'package:fitness_tracker/models/project.dart';
import 'package:fitness_tracker/screens/add_data.dart';
import 'package:fitness_tracker/screens/project_data_page.dart';
import 'package:flutter/material.dart';
import 'package:logger/logger.dart';

import '../api/api.dart';
import '../api/network.dart';
import '../services/database_helper.dart';
import '../widgets/message.dart';

class MainSection extends StatefulWidget {
  const MainSection({super.key});

  @override
  _MainSectionState createState() => _MainSectionState();
}

class _MainSectionState extends State<MainSection> {
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
      getProjects();
    });
  }

  getProjects() async {
    if (!mounted) return;
    setState(() {
      isLoading = true;
    });
    if (online) {
      try {
        //projects = await DatabaseHelper.getProjects();
        projects = await ApiService.instance.getProjects();
        DatabaseHelper.updateProjects(projects);
      } catch (e) {
        logger.e(e);
        message(context, "Error connecting to the server", "Error");
      }
    } else {
      projects = await DatabaseHelper.getProjects();
    }

    setState(() {
      isLoading = false;
    });
  }

  saveProjectData(ProjectData projectData) async {
    if (!mounted) return;
    setState(() {
      isLoading = true;
    });
      try {
        final ProjectData received =
            await ApiService.instance.addProjectData(projectData);
        DatabaseHelper.addProjectData(received);
      } catch (e) {
        DatabaseHelper.addProjectData(projectData);
        logger.e(e);
      }
    setState(() {
      isLoading = false;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Main section'),
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
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.push(
                  context, MaterialPageRoute(builder: ((context) => const AddData())))
              .then((value) {
            if (value != null) {
              setState(() {
                saveProjectData(value);
              });
            }
          });
        },
        tooltip: 'Add projects',
        child: const Icon(Icons.add),
      ),
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
