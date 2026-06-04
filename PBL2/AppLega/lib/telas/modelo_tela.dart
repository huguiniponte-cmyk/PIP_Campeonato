import 'package:flutter/material.dart';
import 'package:pbl2/widgets/fundo_padrao.dart';

//*********Instruções********
//1. Copiar este ficheiro para o seu arquivo da tela.
//2. Renomear o nome da tela para o nome da tela que voce esta criando.
//3. Desenvolver o codigo dentro do Column

class ModeloDeTela extends StatelessWidget {
  const ModeloDeTela({super.key});

  @override
  Widget build(BuildContext context) {
    return const FundoPadrao(
      child: Padding(
        padding: EdgeInsets.all(
            24.0), // Espaco entre as bordas da tela e o conteudo, podem modificar.
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            //Titulo da tela, podem apagar ou modificar.
            Text(
              'Modelo de Tela',
              style: TextStyle(
                  fontSize: 24,
                  fontWeight: FontWeight.bold,
                  color: Colors.white),
            ),

            SizedBox(
                height:
                    20), // Espaco entre o titulo e o conteudo. (podem modificar)
          ],
        ),
      ),
    );
  }
}
