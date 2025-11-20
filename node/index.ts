import { PutObjectCommand, S3Client } from "@aws-sdk/client-s3";
import { readFileSync } from "fs";

const REGION = process.env.REGION!;
const BUCKET = process.env.BUCKET!;

const s3 = new S3Client({
  region: REGION,
  credentials: {
    accessKeyId: process.env.AWS_ACCESS_KEY_ID!,
    secretAccessKey: process.env.AWS_SECRET_ACCESS_KEY!,
  },
});

async function upload(path: string, key: string) {
  const arquivo = readFileSync(path);

  const comando = new PutObjectCommand({
    Bucket: BUCKET,
    Key: key,
    Body: arquivo,
    ContentType: "text/plain",
  });

  try {
    const envio = await s3.send(comando);
    console.log(envio);
  } catch {
    console.log("não enviou");
  }
}

const PATH_AGENDAMENTOS = "/app/dados/agendamentos.txt";
const PATH_PACIENTES = "/app/dados/pacientes.txt";

function sleep(ms: number) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

let agendamentosAntes = readFileSync(PATH_AGENDAMENTOS, "utf8");
let pacientesAntes = readFileSync(PATH_PACIENTES, "utf8");

async function watcher() {
  while (true) {
    const agendamentosDepois = readFileSync(PATH_AGENDAMENTOS, "utf8");
    const pacientesDepois = readFileSync(PATH_PACIENTES, "utf8");

    if (agendamentosAntes !== agendamentosDepois) {
      console.log("Subindo agendamentos.txt");
      await upload(PATH_AGENDAMENTOS, "agendamentos.txt");
      agendamentosAntes = agendamentosDepois;
    }

    if (pacientesAntes !== pacientesDepois) {
      console.log("Subindo pacientes.txt");
      await upload(PATH_PACIENTES, "pacientes.txt");
      pacientesAntes = pacientesDepois;
    }

    await sleep(500);
  }
}

watcher()