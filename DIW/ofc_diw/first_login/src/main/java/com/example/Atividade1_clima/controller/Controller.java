package com.example.Atividade1_clima.controller;

import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.GetMapping;

import com.example.Atividade1_clima.service.ClimaService;

@RestController
public class Controller 
{
    private final ClimaService service;

    public Controller(ClimaService service)
    {
        this.service = service;
    }

    @GetMapping("/climaBH")
    public String preverTempoBH()
     {
        return service.preverTempoBH();
     }
     
    @GetMapping("/clima/{cidade}")
    public String preverTempo(@PathVariable String cidade) 
    {
        return service.preverTempo(cidade);
    }        
}
