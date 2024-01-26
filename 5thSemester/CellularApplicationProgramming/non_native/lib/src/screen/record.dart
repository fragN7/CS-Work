import 'package:flutter/material.dart';
import '../model/record.dart';
import '../repo/boxes.dart';

class RecordPage extends StatelessWidget {
  const RecordPage({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    Record record = ModalRoute.of(context)!.settings.arguments as Record;

    return Scaffold(
      appBar: AppBar(
        title: Text('${record.gameOpening} V ${record.opponentName}'),
        centerTitle: true,
        bottom: const PreferredSize(
          preferredSize: Size.fromHeight(1.0),
          child: Divider(color: Colors.white),
        ),
        actions: [
          IconButton(
            icon: const Icon(Icons.edit),
            onPressed: () {
              Navigator.pushNamed(context, '/view/edit', arguments: record);
            },
          ),
          IconButton(
            icon: const Icon(Icons.delete),
            onPressed: () {
              deleteRecord(context, record);
            },
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Text(
                '${record.opponentName}(${record.opponentRating}) v You(${record.rating})', // Replace this with how you want to display the record details
                style: const TextStyle(color: Colors.white, fontSize: 24), // Set text color to white and adjust font size
              ),
              const SizedBox(height: 16), // Add some space between the text and buttons
              // Additional attributes displayed using different heading styles
              Text(
                '${record.opponentProfile}',
                style: const TextStyle(color: Colors.white, fontSize: 16), // h2 style
              ),
              const SizedBox(height: 16),
              Text(
                record.gameOutcome,
                style: const TextStyle(color: Colors.white, fontSize: 14), // h3 style
              ),
              const SizedBox(height: 16),
              Text(
                '${record.gameTag}',
                style: const TextStyle(color: Colors.white, fontSize: 16), // h2 style
              ),
              const SizedBox(height: 16),
              Text(
                '${record.notes}',
                style: const TextStyle(color: Colors.white, fontSize: 14), // h3 style
              ),
              const SizedBox(height: 24), // Add more space between the details and buttons
            ],
          ),
        ),
      ),
    );
  }

  void deleteRecord(BuildContext context, Record record){
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          title: const Text('Confirm Deletion'),
          content: Text('Are you sure you want to delete this record? ${record.id.toString()}'),
          actions: <Widget>[
            TextButton(
              onPressed: () {
                deleteRecordMethod(record);

                Navigator.of(context).pop();
                Navigator.of(context).pop();
              },
              child: const Text('Delete'),
            ),
            TextButton(
              onPressed: () {
                Navigator.of(context).pop(); // Close the confirmation dialog
              },
              child: const Text('Cancel'),
            ),
          ],
        );
      },
    );
  }

  Future deleteRecordMethod(record) async {
    final box = Boxes.getRecords();
    await box.deleteAt(record.id);
  }

}
