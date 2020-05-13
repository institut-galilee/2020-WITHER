-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le :  mer. 13 mai 2020 à 21:26
-- Version du serveur :  5.7.26
-- Version de PHP :  7.2.18

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `iot_project`
--

-- --------------------------------------------------------

--
-- Structure de la table `personne`
--

DROP TABLE IF EXISTS `personne`;
CREATE TABLE IF NOT EXISTS `personne` (
  `id_personne` int(11) NOT NULL AUTO_INCREMENT,
  `id_user` varchar(255) NOT NULL,
  `mdp_user` varchar(255) NOT NULL,
  PRIMARY KEY (`id_personne`),
  UNIQUE KEY `id_user` (`id_user`)
) ENGINE=MyISAM AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `personne`
--

INSERT INTO `personne` (`id_personne`, `id_user`, `mdp_user`) VALUES
(1, 'a', 'a'),
(2, 'b', 'b'),
(3, 'bonjour', 'bonjour'),
(4, 'c', 'c'),
(5, 'mathieu', 'mathieu'),
(6, 'autre', '123'),
(7, 'lambda', '123'),
(8, 'personne', '123'),
(9, 'harry', '123');

-- --------------------------------------------------------

--
-- Structure de la table `reglages`
--

DROP TABLE IF EXISTS `reglages`;
CREATE TABLE IF NOT EXISTS `reglages` (
  `id_personne` int(11) NOT NULL,
  `temp_min` int(11) NOT NULL,
  `temp_max` int(11) NOT NULL,
  `qte_nourriture` int(11) NOT NULL,
  `H1_nourriture` time NOT NULL,
  `H2_nourriture` time DEFAULT NULL,
  `H3_nourriture` time DEFAULT NULL,
  `H4_nourriture` time DEFAULT NULL,
  KEY `fk_reglages_id_personne_personne_id_personne` (`id_personne`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `reglages`
--

INSERT INTO `reglages` (`id_personne`, `temp_min`, `temp_max`, `qte_nourriture`, `H1_nourriture`, `H2_nourriture`, `H3_nourriture`, `H4_nourriture`) VALUES
(1, 1, 1, 25, '02:01:00', '01:01:00', '01:01:00', '01:01:00'),
(2, 1, 1, 15, '03:04:00', '00:00:00', '00:00:00', '00:00:00'),
(5, 6, 8, 20, '00:06:00', '00:00:00', '00:00:00', '00:00:00'),
(7, 10, 31, 20, '20:00:00', '00:00:00', '00:00:00', '00:00:00'),
(8, 10, 28, 20, '18:00:00', '10:20:00', '00:00:00', '00:00:00'),
(9, 7, 28, 20, '20:00:00', '00:00:00', '00:00:00', '00:00:00');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
