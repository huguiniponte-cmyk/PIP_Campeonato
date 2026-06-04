import 'package:flutter/material.dart';

class AppColors {
  static const Color colorBackground = Color(0xFF252F60);

  // Cor dos cartões dos torneios
  static const Color cardTorneio = Color(0xFF1E264D);

  // Cor do status do torneio
  static const Color statusActive = Color(0xFF00E676);
  static const Color statusFinished = Color(0xFFFF1744);

  // Cores de Texto
  static const Color textPrimary = Colors.white;
  static const Color textSecondary = Colors.white70;

  static const LinearGradient backgroundGradient = LinearGradient(
    begin: Alignment.topLeft,
    end: Alignment.bottomRight,
    colors: [
      colorBackground,
    ],
  );
}
