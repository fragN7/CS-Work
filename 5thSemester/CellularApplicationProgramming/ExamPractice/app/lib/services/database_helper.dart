import 'package:fitness_tracker/models/fitness_data.dart';
import 'package:fitness_tracker/models/project.dart';
import 'package:logger/logger.dart';
import 'package:path/path.dart';
import 'package:path_provider/path_provider.dart';
import 'package:sqflite/sqflite.dart';

class DatabaseHelper {
  static const int _version = 1;
  static const String _name = 'project.db';
  static Logger logger = Logger();

  static Future<Database> _getDB() async {
    final directory = await getExternalStorageDirectory();
    final path = join(directory!.path, _name);
    return await openDatabase(path, version: _version,
        onCreate: (db, version) async {
      await db.execute('''
        CREATE TABLE project_data (
          id INTEGER PRIMARY KEY,
          name TEXT NOT NULL,
          team TEXT NOT NULL,
          details TEXT NOT NULL,
          status TEXT NOT NULL,
          members INTEGER NOT NULL,
          type TEXT NOT NULL
        )
      ''');
    });
  }

  static Future<List<String>> getProjects() async {
    final db = await _getDB();
    final result = await db.query('project_data');
    logger.log(Level.info, "getProjects() result: $result");
    return (result)
        .map((e) => ProjectData.fromJson(e))
        .map((e) => e.toString())
        .toList();
  }

  static Future<ProjectData> getProject(int id) async {
    final db = await _getDB();
    final result =
        await db.query('project_data', where: 'id = ?', whereArgs: [id]);
    logger.log(Level.info, "getProject() result: $result");
    return result.map((e) => ProjectData.fromJson(e)).first;
  }


  static Future<ProjectData> addProjectData(ProjectData projectData) async {
    final db = await _getDB();
    final id = await db.insert('project_data', {'project': projectData});
    logger.log(Level.info, "addProjectData() id: $id");
    return projectData.copy(id: id);
  }

  static Future<void> updateProjects(List<String> projects) async {
    final db = await _getDB();
    await db.delete('project_data');
    for (var project in projects) {
      await db.insert('project_data', {'project': project});
    }
    logger.log(Level.info, "updateProjects() projects: $projects");
  }

  // close database
  static Future<void> close() async {
    final db = await _getDB();
    await db.close();
  }
}
