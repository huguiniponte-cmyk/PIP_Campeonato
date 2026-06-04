import 'package:flutter/material.dart';
import 'package:pbl2/theme/colors.dart';

class FundoPadrao extends StatelessWidget {
  final Widget child;

  const FundoPadrao({Key? key, required this.child}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    final larguraTela = MediaQuery.of(context).size.width;

    return Scaffold(
      backgroundColor: AppColors.colorBackground,
      body: Stack(
        children: [
          // letra G no fundo
          Positioned(
            bottom: -60,
            right: -100,
            child: Opacity(
              opacity: 0.4,
              child: Image.asset(
                'assets/letrag.png',
                width: larguraTela * 0.85,
                fit: BoxFit.contain,
              ),
            ),
          ),

          SizedBox.expand(
            child: SafeArea(
              child: child,
            ),
          ),
        ],
      ),
    );
  }
}
