import 'package:flutter/material.dart';
import 'package:hive_flutter/hive_flutter.dart';

import '../repo/boxes.dart';
import '../model/record.dart';

class RecordsPage extends StatefulWidget {
  const RecordsPage({super.key});

  @override
  State<RecordsPage> createState() => _RecordsPageState();
}

class _EndTopFloatingActionButtonLocation extends FloatingActionButtonLocation {
  @override
  Offset getOffset(ScaffoldPrelayoutGeometry scaffoldGeometry) {
    final double x = scaffoldGeometry.scaffoldSize.width - 48.0; // Adjust the value as needed
    const double y = 4; // Adjust the value as needed
    return Offset(x, y);
  }
}

class _RecordsPageState extends State<RecordsPage> {

  @override
  void dispose() {
    Hive.close();
    super.dispose();
  }

  //List of records and add button
  @override
  Widget build(BuildContext context) => Scaffold(
    appBar: AppBar(
      title: const Text('CHESS GAMES RECORDS'),
      centerTitle: true,
      bottom: const PreferredSize(
        preferredSize: Size.fromHeight(1.0), // Height of the line
        child: Divider(color: Colors.white), // Divider widget as a line
      ),
    ),
    floatingActionButton: FloatingActionButton(
      backgroundColor: Colors.black,
      mini: true, // Set the FAB to be smaller
      child: const Icon(Icons.add),
      onPressed: () => Navigator.pushNamed(context, '/add'),
    ),
    floatingActionButtonLocation: _EndTopFloatingActionButtonLocation(), // Positioning the FAB
    body: ValueListenableBuilder<Box<Record>>(
      valueListenable: Boxes.getRecords().listenable(),
      builder: (context, box, _) {
        final records = box.values.toList().cast<Record>();
        return buildContent(records);
      },
    ),
  );


  // Defining the box where the record will be
  Widget buildContent(List<Record> records) {
    if (records.isEmpty) {
      return const Center(
        child: Text(
          'No records yet!',
          style: TextStyle(fontSize: 24)
        ),
      );
    } else {
      return ListView.separated(
        padding: const EdgeInsets.all(16),
        itemCount: records.length,
        separatorBuilder: (BuildContext context, int index) => const SizedBox(height: 8), // Add 16px spacing between records
        itemBuilder: (BuildContext context, int index) {
          final record = records[index];
          return buildRecord(context, record);
        },
      );
    }
  }


  // Individual record populating
  Widget buildRecord(BuildContext context, Record record) {
    return GestureDetector(
      onTap: () {
        Navigator.pushNamed(context, '/view', arguments: record);
      },
      child: Card(
        color: Colors.grey[800],
        child: ListTile( // Using ListTile for the ExpansionTile appearance
          tileColor: Colors.grey[800], // Set tile color if needed
          title: Text(
            "${record.gameOpening} V ${record.opponentName}",
            maxLines: 2,
            style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 18, color: Colors.white),
          ),
          subtitle: Text(
            record.rating.toString(),
            style: const TextStyle(color: Colors.white),
          ),
          trailing: Text(
            record.gameOutcome.toString(),
            style: const TextStyle(color: Colors.white),
          ),
        ),
      ),
    );
  }




}