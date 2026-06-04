import 'package:flutter/material.dart';

class AppColors {
  static const Color bgGradientStart = Color(
    0xFF252F60,
  ); // Cor de Fundo Principal
  static const Color bgGradientMiddle = Color(
    0xFF2F4095,
  ); // Cor de Fundo Intermediária
  static const Color bgGradientEnd = Color(0xFF2E3F93); // Cores de Fundo

  // Cor dos blocos/cartões dos torneios
  static const Color cardBg = Color(0xFF1E264D); // Cor de Fundo dos Cartões

  // Cores dos Indicadores de Status (Bolas)
  static const Color statusGreen = Color(
    0xFF00E676,
  ); // Verde para "Em Andamento"
  static const Color statusRed = Color(
    0xFFFF1744,
  ); // Vermelho para "Finalizado"

  // Cores de Texto
  static const Color textPrimary = Colors.white;
  static const Color textSecondary = Colors.white70;

  static const LinearGradient backgroundGradient = LinearGradient(
    begin: Alignment.topLeft,
    end: Alignment.bottomRight,
    colors: [bgGradientStart, bgGradientMiddle, bgGradientEnd],
    stops: [0.09, 0.75, 0.84],
  );
}
