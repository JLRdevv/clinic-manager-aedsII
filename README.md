# Clinic manager
Sistema de agendamento pra clínica médica

---
Esse projeto foi desenvolvido por **João Lucas Rodrigues** & **Maria Eduarda Alves** na disciplina de Algoritmos e Estruturas de Dados II
Alguns dos requisitos técnicos foram:
+ Uso de arquivos para gravar e ler dados;
+ Uso de Structs e Vectors;
+ Limite de cadastros de pacientes e agendamentos;
+ Algumas operações CRUD;
+ Ser desenvolvido em C++.

---
## O que fizemos além?
+ Transformamos o projeto em uma API REST usando o framework **crowcpp**.
+ Dockerizamos a aplicação e aplicamos volumes pra persistência dos dados dos arquivos.
+ Criamos um script que assiste a mudança dos arquivos e as envia pra um AWS S3.

---
# Como rodar?

Clone o repositório
```
git clone https://github.com/JLRdevv/clinic-manager-aedsII
```

Entre na pasta
```
cd clinic-manager-aedsII
```

Suba o compose
```
docker compose up
```
> Docker engine deve estar rodando em sua máquina.

---
## Documentação
Os endpoints dessa API estão documentados no API DOG:
[Acesse a documentação](https://bpm0hgqr0w.apidog.io/agendamentos-24590606e0)

### OBS:
> Para usar a funcionalidade de subir os arquivos no S3, você deve criar e preencher o arquivo .env dentro da pasta /node

> Para criar a chave de acesso você deve criar um usuário no AMI com permissões de put no S3.

