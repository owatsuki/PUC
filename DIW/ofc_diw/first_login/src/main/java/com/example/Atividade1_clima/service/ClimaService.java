package com.example.Atividade1_clima.service;

import org.springframework.http.ResponseEntity;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

@Service
public class ClimaService 
{
    @Value("${api.url.cidade}")
    private String apiUrlCidade;

    @Value("${api.url.bh}")
    private String apiUrlBH;


    private String consultarURL(String apiUrl)
    {
        String dados = "";
        RestTemplate restTemplate = new RestTemplate();
        ResponseEntity<String> responseEntity = restTemplate.getForEntity(apiUrl, String.class);

        if (responseEntity.getStatusCode().is2xxSuccessful()) 
        {
            dados = responseEntity.getBody();
        }
        else
        {
            dados = "Falha ao obter dados.Códigos de status: " + responseEntity.getStatusCode();
        }
        return dados;
    }
    public String preverTempoBH()
    {
        return consultarURL(apiUrlBH);
    }
    public String preverTempo(String cidade)
    {
        cidade = cidade.replace("-", " ");
        return consultarURL(apiUrlCidade + cidade + "&count=1&language=pt&format=json");
    }
}
