// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'record.dart';

// **************************************************************************
// TypeAdapterGenerator
// **************************************************************************

class RecordAdapter extends TypeAdapter<Record> {
  @override
  final int typeId = 0;

  @override
  Record read(BinaryReader reader) {
    final numOfFields = reader.readByte();
    final fields = <int, dynamic>{
      for (int i = 0; i < numOfFields; i++) reader.readByte(): reader.read(),
    };
    return Record(
      id: fields[0] as int,
      rating: fields[1] as int,
      opponentName: fields[2] as String,
      opponentRating: fields[3] as int,
      gameOutcome: fields[5] as String,
      gameOpening: fields[6] as String,
    )
      ..opponentProfile = fields[4] as String?
      ..gameTag = fields[7] as String?
      ..notes = fields[8] as String?;
  }

  @override
  void write(BinaryWriter writer, Record obj) {
    writer
      ..writeByte(9)
      ..writeByte(0)
      ..write(obj.id)
      ..writeByte(1)
      ..write(obj.rating)
      ..writeByte(2)
      ..write(obj.opponentName)
      ..writeByte(3)
      ..write(obj.opponentRating)
      ..writeByte(4)
      ..write(obj.opponentProfile)
      ..writeByte(5)
      ..write(obj.gameOutcome)
      ..writeByte(6)
      ..write(obj.gameOpening)
      ..writeByte(7)
      ..write(obj.gameTag)
      ..writeByte(8)
      ..write(obj.notes);
  }

  @override
  int get hashCode => typeId.hashCode;

  @override
  bool operator ==(Object other) =>
      identical(this, other) ||
      other is RecordAdapter &&
          runtimeType == other.runtimeType &&
          typeId == other.typeId;
}
