import 'package:hive/hive.dart';
import '../model/record.dart';

class Boxes {
  static Box<Record> getRecords() => Hive.box<Record>('records');
}
