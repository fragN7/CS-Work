import 'package:flutter/material.dart';
import 'package:hive_flutter/hive_flutter.dart';
import 'package:non_native/src/model/record.dart';
import 'package:non_native/src/screen/add.dart';
import 'package:non_native/src/screen/record.dart';
import 'package:non_native/src/screen/records.dart';
import 'package:non_native/src/screen/update.dart';


void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  await Hive.initFlutter();

  Hive.registerAdapter(RecordAdapter());
  await Hive.openBox<Record>('records');

  runApp(const MainApp());
}

class MainApp extends StatelessWidget {
  static const String title = 'Chess Records';
  const MainApp({super.key});


  @override
  Widget build(BuildContext context) {

    MaterialColor blackSwatch = const MaterialColor(0xFF000000, {
      50: Color(0xFF000000),
      100: Color(0xFF000000),
      200: Color(0xFF000000),
      300: Color(0xFF000000),
      400: Color(0xFF000000),
      500: Color(0xFF000000),
      600: Color(0xFF000000),
      700: Color(0xFF000000),
      800: Color(0xFF000000),
      900: Color(0xFF000000),
    });

    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: title,
      theme: ThemeData(
        primarySwatch: blackSwatch,
        scaffoldBackgroundColor: Colors.black
      ),
      initialRoute: '/',
      routes: {
        '/': (context) => const RecordsPage(),
        '/add': (context) => const AddRecordPage(),
        '/view': (context) => const RecordPage(),
        '/view/edit': (context) => const UpdateRecordPage(),
      },
    );
  }
}


