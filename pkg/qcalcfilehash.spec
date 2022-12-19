Summary:	Hash calculator
Name:		qcalcfilehash
Version:	1.1.0
Release:	1
License:	GPLv3+
Group:		File tools
Url:		https://bitbucket.org/admsasha/qcalcfilehash
Source0:	https://bitbucket.org/admsasha/QCalcFileHash/downloads/%{name}-%{version}.tar.gz

BuildRequires:	qt5-linguist-tools
BuildRequires:	pkgconfig(openssl)
BuildRequires:	pkgconfig(Qt5Core)
BuildRequires:	pkgconfig(Qt5Gui)
BuildRequires:	pkgconfig(Qt5Widgets)
# supports GOST hashes if it is installed
Recommends:	openssl-gost-engine

%description
Hash calculator (SHA1, SHA-224, SHA-256, SHA-384, SHA-512, MD5, CRC32, CRC8
and also GOST R 34.11-94, GOST R 34-11-2012 (Streebog) 256 and 512 bit).

%files
%doc README.md
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/%{name}/
%{_iconsdir}/hicolor/*/apps/%{name}.png

#----------------------------------------------------------------------------

%prep
%setup -q

%build
%qmake_qt5
%make

%install
%make_install INSTALL_ROOT=%{buildroot}
