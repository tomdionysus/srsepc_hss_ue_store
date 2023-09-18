-- MySQL dump 10.13  Distrib 8.0.33, for macos12.6 (x86_64)
--
-- Host: localhost    Database: srsepc
-- ------------------------------------------------------
-- Server version	8.0.33

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `ue_subscriber`
--

DROP TABLE IF EXISTS `ue_subscriber`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ue_subscriber` (
  `imsi` bigint NOT NULL,
  `name` varchar(256) NOT NULL,
  `auth` enum('xor','mil') NOT NULL DEFAULT 'mil',
  `key_identifier` binary(16) NOT NULL,
  `op_type` enum('op','opc') DEFAULT 'opc',
  `op_opc` binary(16) DEFAULT NULL,
  `amf` binary(2) NOT NULL,
  `sqn` binary(6) NOT NULL,
  `qci` tinyint NOT NULL,
  `ip_alloc` varchar(15) NOT NULL DEFAULT 'dynamic',
  PRIMARY KEY (`imsi`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ue_subscriber`
--

LOCK TABLES `ue_subscriber` WRITE;
/*!40000 ALTER TABLE `ue_subscriber` DISABLE KEYS */;
INSERT INTO `ue_subscriber` VALUES (530302814353573,'Tom Cully','mil',0x7E3F3F625FD1A72B483F7A3F3F275400,'opc',0x6B3444C5835A5D3FD3AD3F7E3F3F703F,0x3F55,0x010203040506,1,'192.168.11.44');
/*!40000 ALTER TABLE `ue_subscriber` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-09-17 20:41:49
