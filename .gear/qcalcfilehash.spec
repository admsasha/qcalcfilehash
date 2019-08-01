Summary:	Hash calculator
Name:		qcalcfilehash
Version:	1.0.4
Release:	alt1
License:	GPLv2+
Packager:	Alexander Danilov <admsasha@altlinux.org>
Group:		File tools
Url:		https://bitbucket.org/admsasha/qcalcfilehash
Source0:	https://bitbucket.org/admsasha/QCalcFileHash/downloads/%{name}-%{version}.tar.gz
Source1:	%{name}.png

BuildRequires:	qt5-tools
BuildRequires:	pkgconfig(openssl)
BuildRequires:	pkgconfig(Qt5Core)
BuildRequires:	pkgconfig(Qt5Gui)
BuildRequires:	pkgconfig(Qt5Widgets)

%description
Hash calculator (SHA1, SHA-224, SHA-256, SHA-384, SHA-512, MD5, CRC32, CRC8).

%files
%doc README.md
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%dir %{_datadir}/%{name}/
%{_datadir}/%{name}/*
%{_iconsdir}/hicolor/32x32/apps/%{name}.png

#----------------------------------------------------------------------------

%prep
%setup -q

%build
%qmake_qt5
lupdate-qt5 ./QCalcFileHash.pro
lrelease-qt5 ./QCalcFileHash.pro
%make

%install
mkdir -p %{buildroot}%{_bindir}
install -m 755 Bin/%{name} %{buildroot}%{_bindir}/%{name}

mkdir -p %{buildroot}%{_datadir}/%{name}
install -m 644 *.qm %{buildroot}%{_datadir}/%{name}/

mkdir -p %{buildroot}%{_iconsdir}/hicolor/32x32/apps/
install -m 644 %{SOURCE1} %{buildroot}%{_iconsdir}/hicolor/32x32/apps/%{name}.png

mkdir -p  %{buildroot}%{_datadir}/applications
cat > %{buildroot}%{_datadir}/applications/%{name}.desktop << EOF
[Desktop Entry]
Name=QCalcFileHash
Comment=Hash calculator
Type=Application
Exec=%{name}
Icon=%{name}
Categories=Utility;Qt;
EOF

%changelog
* Tue Jul 30 2019 Alexander Danilov <admsasha@altlinux.org> 1.0.4-alt1
- release 1.0.4
