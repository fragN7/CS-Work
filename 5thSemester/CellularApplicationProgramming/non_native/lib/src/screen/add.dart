import 'package:flutter/material.dart';
import '../model/record.dart';
import '../repo/boxes.dart';

class AddRecordPage extends StatelessWidget {
  const AddRecordPage({
    Key? key,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          'ADD RECORD',
          style: TextStyle(color: Colors.white),
        ),
        centerTitle: true,
        bottom: const PreferredSize(
          preferredSize: Size.fromHeight(1), // Height of the line
          child: Divider(color: Colors.white), // Divider widget as a line
        ),
      ),
      body: const RecordForm(),
    );
  }
}

class RecordForm extends StatefulWidget {

  const RecordForm({
    Key? key
  }) : super(key: key);

  @override
  State<RecordForm> createState() => _RecordFormState();
}

class _RecordFormState extends State<RecordForm> {
  final formKey = GlobalKey<FormState>();

  final ratingController = TextEditingController();
  final opponentNameController = TextEditingController();
  final opponentRatingController = TextEditingController();
  final opponentProfileController = TextEditingController();
  final gameOutcomeController = TextEditingController();
  final gameOpeningController = TextEditingController();
  final gameTagController = TextEditingController();
  final notesController = TextEditingController();

  @override
  void dispose() {
    ratingController.dispose();
    opponentNameController.dispose();
    opponentRatingController.dispose();
    opponentProfileController.dispose();
    gameOutcomeController.dispose();
    gameOpeningController.dispose();
    gameTagController.dispose();
    notesController.dispose();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Form(
          key: formKey,
          child: Column(
            children: <Widget>[
              const SizedBox(height: 16),
              buildRating(),
              const SizedBox(height: 16),
              buildOpponentName(),
              const SizedBox(height: 16),
              buildOpponentRating(),
              const SizedBox(height: 16),
              buildOpponentProfile(),
              const SizedBox(height: 16),
              buildGameOutcome(),
              const SizedBox(height: 16),
              buildGameOpening(),
              const SizedBox(height: 16),
              buildGameTag(),
              const SizedBox(height: 16),
              buildNotes(),
              const SizedBox(height: 16),
              buildAddButton(context),
              const SizedBox(height: 16),
            ],
          ),
        ),
      ),
    );
  }

  Widget buildRating() => TextFormField(
    controller: ratingController,
    decoration: InputDecoration(
      border: OutlineInputBorder(
        borderSide: BorderSide(color: Colors.grey[800]!), // Set the border color
      ),
      filled: true,
      fillColor: Colors.grey[800], // Set the fill color
      hintText: 'Your Rating *',
      hintStyle: const TextStyle(color: Colors.white), // Set the hint text color
    ),
    keyboardType: TextInputType.number,
    style: const TextStyle(color: Colors.white),
    validator: (rating) =>
    rating != null && int.tryParse(rating) == null
        ? 'Enter a valid number'
        : null,
  );


  Widget buildOpponentName() => TextFormField(
    controller: opponentNameController,
    decoration: InputDecoration(
      border: OutlineInputBorder(
        borderSide: BorderSide(color: Colors.grey[800]!), // Set the border color
      ),
      filled: true,
      fillColor: Colors.grey[800], // Set the fill color
      hintText: 'Opponent Name *',
      hintStyle: const TextStyle(color: Colors.white), // Set the hint text color
    ),
    style: const TextStyle(color: Colors.white),
    validator: (name) =>
    name != null && name.isEmpty ? 'Enter your opponent\'s name' : null,
  );

  Widget buildOpponentRating() => TextFormField(
    controller: opponentRatingController,
    decoration: InputDecoration(
      border: OutlineInputBorder(
        borderSide: BorderSide(color: Colors.grey[800]!), // Set the border color
      ),
      filled: true,
      fillColor: Colors.grey[800], // Set the fill color
      hintText: 'Opponent Rating *',
      hintStyle: const TextStyle(color: Colors.white), // Set the hint text color
    ),
    keyboardType: TextInputType.number,
    style: const TextStyle(color: Colors.white),
    validator: (rating) =>
    rating != null && int.tryParse(rating) == null
        ? 'Enter a valid number'
        : null,
  );

  Widget buildOpponentProfile() => TextFormField(
    controller: opponentProfileController,
    decoration: InputDecoration(
      border: OutlineInputBorder(
        borderSide: BorderSide(color: Colors.grey[800]!), // Set the border color
      ),
      filled: true,
      fillColor: Colors.grey[800], // Set the fill color
      hintText: 'Opponent Profile',
      hintStyle: const TextStyle(color: Colors.white), // Set the hint text color
    ),
    style: const TextStyle(color: Colors.white),
  );

  Widget buildGameOutcome() => TextFormField(
    controller: gameOutcomeController,
    decoration: InputDecoration(
      border: OutlineInputBorder(
        borderSide: BorderSide(color: Colors.grey[800]!), // Set the border color
      ),
      filled: true,
      fillColor: Colors.grey[800], // Set the fill color
      hintText: 'Game Outcome *',
      hintStyle: const TextStyle(color: Colors.white), // Set the hint text color
    ),
    style: const TextStyle(color: Colors.white),
    validator: (name) =>
    name != null && name.isEmpty ? 'Enter the game\'s outcome' : null,
  );

  Widget buildGameOpening() => TextFormField(
    controller: gameOpeningController,
    decoration: InputDecoration(
      border: OutlineInputBorder(
        borderSide: BorderSide(color: Colors.grey[800]!), // Set the border color
      ),
      filled: true,
      fillColor: Colors.grey[800], // Set the fill color
      hintText: 'Game Opening *',
      hintStyle: const TextStyle(color: Colors.white), // Set the hint text color
    ),
    style: const TextStyle(color: Colors.white),
    validator: (name) =>
    name != null && name.isEmpty ? 'Enter the game\'s opening' : null,
  );

  Widget buildGameTag() => TextFormField(
    controller: gameTagController,
    decoration: InputDecoration(
      border: OutlineInputBorder(
        borderSide: BorderSide(color: Colors.grey[800]!), // Set the border color
      ),
      filled: true,
      fillColor: Colors.grey[800], // Set the fill color
      hintText: 'Game Tag',
      hintStyle: const TextStyle(color: Colors.white), // Set the hint text color
    ),
    style: const TextStyle(color: Colors.white),
  );

  Widget buildNotes() => TextFormField(
    controller: notesController,
    decoration: InputDecoration(
      border: OutlineInputBorder(
        borderSide: BorderSide(color: Colors.grey[800]!), // Set the border color
      ),
      filled: true,
      fillColor: Colors.grey[800], // Set the fill color
      hintText: 'Game Notes',
      hintStyle: const TextStyle(color: Colors.white), // Set the hint text color
    ),
    style: const TextStyle(color: Colors.white),
  );

  Widget buildAddButton(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 16.0),
      child: ElevatedButton(
        style: ElevatedButton.styleFrom(
          backgroundColor: Colors.grey[800], // Set the button color
        ),
        onPressed: () {
          final isValid = formKey.currentState!.validate();

          if (isValid) {
            addRecord(
              int.tryParse(ratingController.text) ?? 0,
              opponentNameController.text,
              int.tryParse(opponentRatingController.text) ?? 0,
              opponentProfileController.text,
              gameOutcomeController.text,
              gameOpeningController.text,
              gameTagController.text,
              notesController.text,
            );

            Navigator.of(context).pop(); // Pop the current page when done
          }
        },
        child: const Text('Add Record'),
      ),
    );
  }

  Future addRecord(int rating, String opponentName, int opponentRating, String? opponentProfile,
      String gameOutcome, String gameOpening, String gameTag, String notes) async {

    final record = Record(id: getNextId(), rating: rating, opponentName: opponentName, opponentRating: opponentRating, gameOutcome: gameOutcome, gameOpening: gameOpening,
    opponentProfile: opponentProfile, gameTag: gameTag, notes: notes);

    final box = Boxes.getRecords();
    box.add(record);
  }

  int getNextId() {
    // Implement your logic to get the next available ID for the record
    // For example, find the maximum ID currently in the box and increment it
    final box = Boxes.getRecords();

    int id = box.length;

    return box.length;
  }
}
