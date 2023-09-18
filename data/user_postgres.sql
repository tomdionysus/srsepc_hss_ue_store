DROP TABLE IF EXISTS "ue_subscriber";
DROP TYPE IF EXISTS "public"."user_auth";
DROP TYPE IF EXISTS "public"."user_op_type";

-- Define the "user_auth" enumeration type
CREATE TYPE "public"."user_auth" AS ENUM (
  'xor',
  'mil'
);

-- Define the "user_op_type" enumeration type
CREATE TYPE "public"."user_op_type" AS ENUM (
  'op',
  'opc'
);

CREATE TABLE "ue_subscriber" (
  "imsi" bigint NOT NULL,
  "name" varchar(256) NOT NULL,
  "auth" "public"."user_auth" NOT NULL DEFAULT 'mil',
  "key_identifier" bytea NOT NULL,
  "op_type" "public"."user_op_type" DEFAULT 'opc',
  "op_opc" bytea DEFAULT NULL,
  "amf" bytea NOT NULL,
  "sqn" bytea NOT NULL,
  "qci" smallint NOT NULL,
  "ip_alloc" varchar(15) NOT NULL DEFAULT 'dynamic',
  PRIMARY KEY ("imsi")
);

INSERT INTO "ue_subscriber" (
  "imsi",
  "name",
  "auth",
  "key_identifier",
  "op_type",
  "op_opc",
  "amf",
  "sqn",
  "qci",
  "ip_alloc"
) VALUES (
  530302814353573,
  'Tom Cully',
  'mil',
  E'\\x7E3F3F625FD1A72B483F7A3F3F275400'::bytea,
  'opc',
  E'\\x6B3444C5835A5D3FD3AD3F7E3F3F703F'::bytea,
  E'\\x3F55'::bytea,
  E'\\x010203040506'::bytea,
  1,
  '192.168.11.44'
);
