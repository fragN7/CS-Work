import 'dart:convert';

import 'package:dio/dio.dart';
import 'package:fitness_tracker/models/fitness_data.dart';
import 'package:fitness_tracker/models/project.dart';
import 'package:logger/logger.dart';

const String baseUrl = 'http://localhost:2426';

class ApiService {
  static final ApiService instance = ApiService._init();
  static final Dio dio = Dio();
  var logger = Logger();

  ApiService._init();

  Future<List<String>> getProjects() async {
    logger.log(Level.info, "getProjects() called");
    final response = await dio.get('$baseUrl/projects');
    logger.log(Level.info, "getProjects() response: $response");
    if (response.statusCode == 200) {
      return (response.data as List)
          .map((e) => ProjectData.fromJson(e))
          .map((e) => e.toString())
          .toList();
    } else {
      logger.log(Level.error, "getProjects() error: ${response.statusMessage}");
      throw Exception(response.statusMessage);
    }
  }

  Future<List<String>> getInProgressProjects() async {
    logger.log(Level.info, "getInProgressProjects() called");
    final response = await dio.get('$baseUrl/inProgress');
    logger.log(Level.info, "getInProgressProjects() response: $response");
    if (response.statusCode == 200) {
      return (response.data as List)
          .map((e) => ProjectData.fromJson(e))
          .map((e) => e.toString())
          .toList();
    } else {
      logger.log(Level.error, "getInProgressProjects() error: ${response.statusMessage}");
      throw Exception(response.statusMessage);
    }
  }

  Future<List<String>> getAllProjects() async {
    try {
      logger.log(Level.info, "getAllProjects() called");
      final response = await dio.get('$baseUrl/allProjects');
      logger.log(Level.info, "getAllProjects() response: $response");

      if (response.statusCode == 200) {
        List<ProjectData> projects = (response.data as List)
            .map((e) => ProjectData.fromJson(e))
            .toList();

        // Sort projects by the number of team members in descending order
        projects.sort((a, b) => b.members.compareTo(a.members));

        // Take the top 5 projects
        List<String> top5Projects = projects.take(5).map((e) => e.toString()).toList();

        return top5Projects;
      } else {
        logger.log(Level.error, "getAllProjects() error: ${response.statusMessage}");
        throw Exception(response.statusMessage);
      }
    } catch (e) {
      logger.log(Level.error, "Error in getAllProjects(): $e");
      rethrow;
    }
  }

  Future<ProjectData> getProject(int id) async {
    logger.log(Level.info, "getProject() called");
    final response = await dio.get('$baseUrl/project/$id');
    logger.log(Level.info, "getProject() response: $response");
    if (response.statusCode == 200) {
      return ProjectData.fromJson(response.data);
    } else {
      logger.log(Level.error, "getProject() error: ${response.statusMessage}");
      throw Exception(response.statusMessage);
    }
  }

  Future<ProjectData> putProject(int id) async {
    logger.log(Level.info, "putProject() called");
    final response = await dio.put('$baseUrl/enroll/$id');
    logger.log(Level.info, "putProject() response: $response");
    if (response.statusCode == 200) {
      return ProjectData.fromJson(response.data);
    } else {
      logger.log(Level.error, "putProject() error: ${response.statusMessage}");
      throw Exception(response.statusMessage);
    }
  }

  Future<ProjectData> addProjectData(ProjectData projectData) async {
    logger.log(Level.info, "addProjectData() called");
    final response =
        await dio.post('$baseUrl/project', data: projectData.toJsonWithoutId());
    logger.log(Level.info, "addProjectData() response: $response");
    if (response.statusCode == 200) {
      return ProjectData.fromJson(response.data);
    } else {
      logger.log(
          Level.error, "addProjectData() error: ${response.statusMessage}");
      throw Exception(response.statusMessage);
    }
  }
}
