import 'package:hive/hive.dart';

part 'record.g.dart';

@HiveType(typeId: 0)
class Record {

  Record({
    required this.id,
    required this.rating,
    required this.opponentName,
    required this.opponentRating,
    required this.gameOutcome,
    required this.gameOpening,
    this.opponentProfile,
    this.gameTag,
    this.notes
  });

  @HiveField(0)
  late int id = 0;

  @HiveField(1)
  late int rating = 0;

  @HiveField(2)
  late String opponentName = "";
  @HiveField(3)
  late int opponentRating = 0;
  @HiveField(4)
  late String? opponentProfile = "";
  @HiveField(5)
  late String gameOutcome = "";
  @HiveField(6)
  late String gameOpening = "";
  @HiveField(7)
  late String? gameTag = "";
  @HiveField(8)
  late String? notes = "";
}
